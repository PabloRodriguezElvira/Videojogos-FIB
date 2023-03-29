#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Level.h"


using namespace std;


Level* Level::createLevel(const string& levelFile)
{
	Level* lvl = new Level(levelFile);

	return lvl;
}


Level::Level(const string& levelFile)
{
	loadLevel(levelFile);
}

Level::~Level()
{
	if (lvl != NULL)
		delete lvl;
}

bool Level::loadLevel(const string& levelFile)
{
	ifstream fin;
	string line;
	stringstream sstream;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);																// LEVEL
	if (line.compare(0, 5, "LEVEL") != 0)
		return false;
	getline(fin, line);																// Initial player tile
	sstream.str(line);
	sstream >> initPlayerTile.x >> initPlayerTile.y >> initPlayerAnim;
	
	fin.close();

	return true;
}
