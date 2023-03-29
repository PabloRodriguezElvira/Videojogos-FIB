#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include "Definitions.h"


#include "Enemy.h"
#include <glm/glm.hpp>


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

private:
	bool loadLevel(const string& levelFile);

private:
	int initPlayerAnim;
	glm::ivec2 initPlayerTile;
	int* lvl;

};


#endif // _LEVEL_INCLUDE