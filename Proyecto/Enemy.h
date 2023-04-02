#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Mob.h"


class Enemy : public Mob
{
public:
	char getType() { return type; }
	glm::ivec2 getInitTile() { return initTile; }
	int getInitTileX() { return initTile.x; }
	int getInitTileY() { return initTile.y; }

	void setType(char t) { type = t; }
	void setInitTile(glm::ivec2 iniTile) { initTile = iniTile; }

protected:
	char type;
	glm::ivec2 initTile;

};


#endif // _ENEMY_INCLUDE
