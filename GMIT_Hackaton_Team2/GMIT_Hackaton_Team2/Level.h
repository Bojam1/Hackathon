#ifndef LEVEL_H
#define LEVEL_H

#include "stdafx.h"
#include <fstream>
#include <iostream> 
#include <vector>
#include <string>

class Level
{
public:
	Level();
	static void LoadLevel(string name);
	static vector<string> LoadFromTextFile(string name);


private:
	static const int SCALE;//class variable
	static int currentlevel;
	static const int MAXLEVELS;

};
#endif
