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
	for (Enemy* enemy : enemies)
		if (enemy != NULL)
			delete enemy;
	enemies.clear();
}

bool Level::loadLevel(const string& levelFile)
{
	ifstream fin;
	string line;
	stringstream sstream;
	int i, initAnim;
	char enemyType;
	glm::ivec2 initTile;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);																// LEVEL
	if (line.compare(0, 5, "LEVEL") != 0)
		return false;
	getline(fin, line);																// Initial player tile
	sstream.str(line);
	sstream >> initPlayerTile.x >> initPlayerTile.y >> initPlayerAnim;
	getline(fin, line);																// Number of enemies
	sstream.str(line);
	sstream >> totalEnemies;
	for (i = 0; i < totalEnemies; ++i)
	{
		Enemy* enemy;
		getline(fin, line);															// Enemy type, initial enemy tile & anim
		sstream.str(line);
		sstream >> enemyType >> initTile.x >> initTile.y >> initAnim;
		
		if (enemyType == 'V')
			enemy = new Vaati();

		else if (enemyType == 'S')
			enemy = new Stalfos();

		else enemy = new Stalfos();

		enemy->setType(enemyType);
		enemy->setInitTile(initTile);
		enemy->setInitAnim(initAnim);

		enemies.push_back(enemy);
	}
	
	fin.close();

	return true;
}