#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include "Definitions.h"


#include "Vaati.h"
#include "Stalfos.h"
#include <glm/glm.hpp>
#include <vector>


class Level
{

private:
	Level(const string& levelFile);

public:

	static Level* createLevel(const string& levelFile);

	~Level();

	int getInitPlayerPosX() const { return initPlayerTile.x; }
	int getInitPlayerPosY() const { return initPlayerTile.y; }
	int getInitPlayerAnim() const { return initPlayerAnim; }
	int getStageNumber() const { return stageNumber; }
	glm::vec2 getKeyPosition() const { return keyPosition;  }
	std::vector<Enemy*>* getEnemies() { return &enemies; }

private:
	bool loadLevel(const string& levelFile);

private:
	int initPlayerAnim, totalEnemies;
	glm::ivec2 initPlayerTile;
	std::vector<Enemy*> enemies;
	int* lvl;
	int stageNumber;
	glm::vec2 keyPosition;

};


#endif // _LEVEL_INCLUDE