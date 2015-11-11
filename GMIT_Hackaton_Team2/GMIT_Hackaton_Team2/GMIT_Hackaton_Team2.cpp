#include "stdafx.h"

#include <SDL.h>
#include <SDL_image.h>
#undef main
#include "Box2D\Box2D.h"
#include "Button.h"
#include "Renderer.h"
#include "Sprite.h"
#include "InputHandler.h"
#include "Player.h"
#include "Enemy.h"
#include "MyContactListener.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1248;			//SDL
const int SCREEN_HEIGHT = 704;			//SDL

										//gamestates
const int MENU = 0, PLAY = 1, PAUSE = 2, GAMEOVER = 3;
int gameState;

InputHandler inputHandler = InputHandler();
Sprite* backGroundImage;
Button playButton;
Button exitButton;

// Player
SDL_Rect myRect{ 200, 200, 32, 64 };
Player player;


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


//methods
void Init();
void DrawGame();
void DrawMenu();
void UpdateGame();
bool UpdateMenu(SDL_Event e);
void Reset();
void ClearPointers();


int _tmain(int argc, _TCHAR* argv[])
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);
	gameState = MENU;
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//Box2D
	SDL_Rect worldBounds = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	const b2Vec2 GRAVITY = b2Vec2(0, 1);
	b2World* m_world = new b2World(GRAVITY);
	MyContactListener myContactListenerInstance;
	m_world->SetContactListener(&myContactListenerInstance);
	const float box2D_timestep = 1.0f / 60.0f;
	const int vel_iterations = 6;
	const int pos_iterations = 2;

	//entities
	//Enemy e = new Enemy(



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




			SDL_Event e;
			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0) {
					if (inputHandler.CheckInput(SDLK_ESCAPE, e)) {
						quit = true;
					}
				}

				//controls gameState added in game menu feature
				switch (gameState)
				{
				case MENU:
					//updateMenu
					quit = UpdateMenu(e);
					//draw menu
					DrawMenu();

					break;
				case PLAY:
					UpdateGame();
					m_world->Step(box2D_timestep, vel_iterations, pos_iterations);
					DrawGame();
					break;
				}//end switch

				 // Escape button
				if (inputHandler.CheckInput(SDLK_ESCAPE, e))//::GetInstance()->isKeyPressed(SDLK_ESCAPE))
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
	player.Init(myRect, world);
	gameState = MENU;
	backGroundImage = new Sprite();
	SDL_Rect destination = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect Source = { 0, 0, 1240, 720 };
	backGroundImage->Init("Assets/menu.png", destination, Source);
	destination = { SCREEN_WIDTH / 2 - 166, SCREEN_HEIGHT / 4 - 59, 323, 118 };
	playButton.Init(destination, "Assets/PlayButton.png");
	destination = { SCREEN_WIDTH / 2 - 166, SCREEN_HEIGHT / 4 * 3 - 59, 323, 118 };
	exitButton.Init(destination, "Assets/ExitButton.png");
}
void DrawGame()
{
	Renderer::GetInstance()->ClearRenderer();
	player.Draw();
	/*Call Darw on objects here*/


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
	player.Move(inputHandler);
	player.Update();
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

