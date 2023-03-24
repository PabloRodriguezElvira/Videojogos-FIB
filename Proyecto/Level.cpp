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
	sstream >> initPlayerTile.x >> initPlayerTile.y;
	char tile;
	
//
//
//	char tile;
//
//	
//	
//	getline(fin, line);																// Size of tile map in tiles
//	sstream.str(line);
//	sstream >> mapSize.x >> mapSize.y;
//	getline(fin, line);																// Tile size (físico) & block size (gráfico)
//	sstream.str(line);
//	sstream >> tileSize.x >> tileSize.y >> blockSize.x >> blockSize.y;
//	getline(fin, line);																// Tilesheet
//	sstream.str(line);
//	sstream >> tilesheetFile;
//	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
//	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
//	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
//	tilesheet.setMinFilter(GL_NEAREST);
//	tilesheet.setMagFilter(GL_NEAREST);
//	getline(fin, line);																// Number of tiles in tilesheet
//	sstream.str(line);
//	sstream >> tilesheetSize.x >> tilesheetSize.y;
//	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);
//	getline(fin, line);																// Initial player tile (la que quieras + (-1, -2))
//	sstream.str(line);
//	sstream >> initPlayerTile.x >> initPlayerTile.y;
//
//	map = new int[mapSize.x * mapSize.y];
//	for (int j = 0; j < mapSize.y; j++)
//	{
//		for (int i = 0; i < mapSize.x; i++)
//		{
//			fin.get(tile);
//			if (tile == ' ' || tile == '0')
//				map[j * mapSize.x + i] = 0;
//			else if ('1' <= tile && tile <= '9')
//				map[j * mapSize.x + i] = (tile - int('0'));
//			else
//				map[j * mapSize.x + i] = 10 + (tile - int('A'));
//		}
//		fin.get(tile);
//#ifndef _WIN32
//		fin.get(tile);
//#endif
//	}
#ifndef _WIN32
	  fin.get(tile);
#endif
	fin.close();

	return true;
}
