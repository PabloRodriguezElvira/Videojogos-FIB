#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE


#include "Mob.h"


class Enemy : public Mob
{
public:
	void setType(char t) { type = t; }
	void setInitTile(glm::ivec2 iniTile) { initTile = iniTile; }
	virtual void changeHorizontalDirection() { ; }
	
	char getType() { return type; }
	int getInitTileX() { return initTile.x; }
	int getInitTileY() { return initTile.y; }

protected:
	char type;
	glm::ivec2 initTile;

};


#endif // _ENEMY_INCLUDE
