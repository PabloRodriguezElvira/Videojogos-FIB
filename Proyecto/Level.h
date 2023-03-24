#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include "Definitions.h"


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

private:
	bool loadLevel(const string& levelFile);

private:
	glm::ivec2 initPlayerTile;
	int* lvl;

};


#endif // _LEVEL_INCLUDE