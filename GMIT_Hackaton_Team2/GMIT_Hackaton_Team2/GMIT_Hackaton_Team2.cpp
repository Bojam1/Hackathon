#include "stdafx.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_thread.h>
#include <SDL_timer.h>


#undef main
#include "Box2D\Box2D.h"
#include "Button.h"
#include "Renderer.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "ObstacleManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "Door.h"
#include "MyContactListener.h"
#include "FollowEnemy.h"
#include "Mutex.h"
#include "DataBase.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1248;			//SDL
const int SCREEN_HEIGHT = 704;			//SDL

//320										//gamestates
const int MENU = 0, PLAY = 1, PAUSE = 2, GAMEOVER = 3;
int gameState;
Sprite* backGroundImage;
Button playButton;
Button exitButton;
Door door;
FollowEnemy* enemy;
MyContactListener myContactListenerInstance;
// Player
SDL_Rect myRect{ 200, 200, 32, 64 };
Player player;
//Frame Count
double threadCount = 0;
//box2d stuff
const int SCALE = 32;
b2Vec2 gravity(0.0f, 0.0f);

// Construct a world object, which will hold and simulate the rigid bodies.
b2World *world = new b2World(gravity);
// Prepare for simulation. Typically we use a time step of 1/60 of a
// second (60Hz) and 10 iterations. This provides a high quality simulation
// in most game scenarios.
float32 timeStep = 1.0f / 60.0f;
int32 velocityIterations = 6;
int32 positionIterations = 2;

//Mutex Stuff
static SDL_mutex* mutexOne = SDL_CreateMutex();
DataBase db = DataBase();

//methods
void Init();
void DrawGame();
void DrawMenu();
void UpdateGame();
bool UpdateMenu(SDL_Event e);
void Reset();
void ClearPointers();
void CheckDoorCollisions();
void SetPlayerPosition();
int PlayerMoveThread(void* dataOne);
int DummyThread(void* dataTwo);

bool wentThroughTopDoor, wentThroughBottomDoor, wentThroughRightDoor, wentThroughLeftDoor;
int _tmain(int argc, _TCHAR* argv[])
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
	gameState = MENU;
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	threadCount = 0;
	const float box2D_timestep = 1.0f / 60.0f;
	const int vel_iterations = 6;
	const int pos_iterations = 2;

	enemy = new FollowEnemy(*world, b2Vec2(200, 100), 50, 50);


	//SDL
#pragma region SDL STUFF
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create Renderer for the Window
			if (!Renderer::GetInstance()->Init(window, SCREEN_WIDTH, SCREEN_HEIGHT))
			{
				return 0;
			}

			bool quit = false;
			Init();

			////Run the thread
			//int data = 101;
			//SDL_Thread* threadID = SDL_CreateThread(PlayerMoveThread, "Movement Thread", (void*)data);

			Player* dataOne;


			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0) {
					if (InputHandler::GetInstance()->CheckInput(SDLK_ESCAPE, e)) {
						quit = true;
					}
				}

				//controls gameState added in game menu feature
				switch (gameState)
				{
				case MENU:
					//updateMenu
					quit = UpdateMenu(e);
					DrawMenu();
					break;
				case PLAY:
					dataOne = &player;

					if (threadCount < 1)
					{
						//Run the thread
						SDL_Thread* threadIDTwo = SDL_CreateThread(DummyThread, "Dummy Thread", dataOne);
						SDL_Thread* threadIDOne = SDL_CreateThread(PlayerMoveThread, "Movement Thread", dataOne);
						threadCount++;
					}


					UpdateGame();
					DrawGame();
					world->Step(box2D_timestep, vel_iterations, pos_iterations);
					break;
				}//end switch

		// Escape button
		if (InputHandler::GetInstance()->CheckInput(SDLK_ESCAPE, e))//::GetInstance()->isKeyPressed(SDLK_ESCAPE))
		{
			quit = true;
		}

			}//end while wuit
		}//end else
	}//end else

	ClearPointers();
	return 0;
}

void Init()
{
	door = Door();
	door.LoadRectangle();
	enemy->Init("Assets/enemy.png");
	wentThroughBottomDoor = wentThroughLeftDoor = wentThroughRightDoor = wentThroughTopDoor = false;
	player.Init(myRect, world);
	//db.Write(player);
	Level::LoadLevel("Level1.txt", world);
	gameState = MENU;
	backGroundImage = new Sprite();
	SDL_Rect destination = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect Source = { 0, 0, 1240, 720 };
	backGroundImage->Init("Assets/menu.png", destination, Source);
	destination = { SCREEN_WIDTH / 2 - 166, SCREEN_HEIGHT / 4 - 59, 323, 118 };
	playButton.Init(destination, "Assets/PlayButton.png");
	destination = { SCREEN_WIDTH / 2 - 166, SCREEN_HEIGHT / 4 * 3 - 59, 323, 118 };
	exitButton.Init(destination, "Assets/ExitButton.png");
	world->SetContactListener(&myContactListenerInstance);
}

void DrawGame()
{
	Renderer::GetInstance()->ClearRenderer();


	/*Call Darw on objects here*/
	
	ObstacleManager::GetInstance()->Draw();
	player.Draw();
	enemy->Draw();

	Renderer::GetInstance()->RenderScreen();
}
void DrawMenu()
{
	Renderer::GetInstance()->ClearRenderer();

	/*Call Darw on objects here*/
	backGroundImage->Draw();
	playButton.Draw();
	exitButton.Draw();

	Renderer::GetInstance()->RenderScreen();
}

bool UpdateMenu(SDL_Event e)
{
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		//If the left mouse button was pressed
		if (e.button.button == SDL_BUTTON_LEFT) {
			//Get the mouse offsets
			int mouse_x = e.button.x;
			int mouse_y = e.button.y;
			//SDL_Log("Mouse Button 1 (left) is pressed. x = " + x );
			std::cout << "Mouse Button 1 (left) is pressed. x = " << mouse_x << ", y = " << mouse_y << std::endl;
			if (playButton.IsClicked(mouse_x, mouse_y)) {
				gameState = PLAY;
			}
			else if (exitButton.IsClicked(mouse_x, mouse_y)) {
				return true;
			}
		}
	}
	return false;
}
void UpdateGame()
{

	enemy->Update(player.getPos());
	//player.Move(inputHandler);
	player.Update();
	if (enemy->GetTakePlayershealth()) {
		//player.Add_SubHealth(-1);
		enemy->setTakePlayershealth(false);
	}
	//cout << "Player X Position = " + player.getRectangle().x << endl;
	//cout << "Player Y Position = " + player.getRectangle().y << endl;
	//cout << "Door X Position = " + door.GetTopDoorRect().x << endl;
	//cout << "Door Y Position = " + door.GetTopDoorRect().y << endl;
	//CheckDoorCollisions();
	world->Step(timeStep, velocityIterations, positionIterations);
}

void Reset()
{

}

void ClearPointers()
{
	delete world;
	delete backGroundImage;
}

void CheckDoorCollisions()
{

	if (player.getPos().y > 680)
	{
		if (door.CheckBottomDoorCollisions(&player.getRectangle()))
		{
			if (wentThroughBottomDoor == false)
			{
				ObstacleManager::GetInstance()->ResetRoom(world);
				door.LoadRoom();
				Level::LoadLevel(door.filePath, world);
				wentThroughBottomDoor = true;
				SetPlayerPosition();
			}
		}
	}

	if (player.getPos().x < 100)
	{
		if (door.CheckLeftDoorCollisions(&player.getRectangle()))
		{
			if (wentThroughLeftDoor == false)
			{
				ObstacleManager::GetInstance()->ResetRoom(world);
				door.LoadRoom();
				Level::LoadLevel(door.filePath, world);
				wentThroughLeftDoor = true;
				SetPlayerPosition();
			}
		}
	}

	if (player.getPos().x > 1100)
	{
		if (door.CheckRightDoorCollisions(&player.getRectangle()))
		{
			if (wentThroughRightDoor == false)
			{
				ObstacleManager::GetInstance()->ResetRoom(world);
				door.LoadRoom();
				Level::LoadLevel(door.filePath, world);
				wentThroughRightDoor = true;
				SetPlayerPosition();
			}
		}
	}

	if (player.getPos().y < 100)
	{
		if (door.CheckTopDoorCollisions(&player.getRectangle()))
		{
			if (wentThroughTopDoor == false)
			{
				ObstacleManager::GetInstance()->ResetRoom(world);
				door.LoadRoom();
				Level::LoadLevel(door.filePath, world);
				wentThroughTopDoor = true;
				SetPlayerPosition();
			}
		}
	}
}

void SetPlayerPosition()
{
	
	if (wentThroughBottomDoor)
	{
		player.getBody()->SetTransform(b2Vec2(615, 80), player.getBody()->GetAngle());
		wentThroughBottomDoor = false;
	}

	if (wentThroughLeftDoor)
	{
		player.getBody()->SetTransform(b2Vec2(1170, 325), player.getBody()->GetAngle());
		wentThroughLeftDoor = false;
	}

	if (wentThroughRightDoor)
	{
		player.getBody()->SetTransform(b2Vec2(70, 325), player.getBody()->GetAngle());
		wentThroughRightDoor = false;
	}
	
	if (wentThroughTopDoor)
	{
		player.getBody()->SetTransform(b2Vec2(615, 620), player.getBody()->GetAngle());
		wentThroughTopDoor = false;
	}
}

int PlayerMoveThread(void* data)
{
	while (true)
	{
		//lock
		SDL_LockMutex(mutexOne);


		const Uint8 *keys = SDL_GetKeyboardState(NULL);

		b2Vec2 result;

		if (keys[SDL_SCANCODE_A]) {
			result = b2Vec2(-2, 0);
		}

		else if (keys[SDL_SCANCODE_D]) {
			result = b2Vec2(2, 0);
		}

		else if (keys[SDL_SCANCODE_W]) {
			result = b2Vec2(0, -2);
		}

		else if (keys[SDL_SCANCODE_S]) {
			result = b2Vec2(0, 2);
		}

		else if (!keys[SDL_SCANCODE_D] && !keys[SDL_SCANCODE_A] && !keys[SDL_SCANCODE_W] && !keys[SDL_SCANCODE_S])
		{
			result = b2Vec2(1, 0);
		}

		//Mutex* temp = Mutex::GetInstance();

		
		
		db.Write(result);
		//std::cout << "Move Thread," << endl;
		//SDL_UnlockMutex(mutexOne);
		//unlock
	}
	return 0;
}

int DummyThread(void* data)
{
	//Mutex* temp = Mutex::GetInstance();
		//lock
	while (true)
	{
		//SDL_LockMutex(mutexOne);
		//std::cout << "Dummy Thread, Player Pos = : " << player.getPos().x << ", " << player.getPos().y << ";" << endl;
		////unlock
		//SDL_UnlockMutex(mutexOne);
		b2Vec2 result = db.Read();
		std::cout << result.x << ", " << result.y << std::endl;
		player.getBody()->ApplyLinearImpulse(result, b2Vec2(0, 0), true);
	}
	return 0;
}