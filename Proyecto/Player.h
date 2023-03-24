#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Mob.h"
#include "Sprite.h"
#include "TileMap.h"
#include <glm/glm.hpp>


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player : public Mob
{

protected:
	void initMob();
	void updateMob(int deltaTime);

	string setSpriteSheet();
	glm::ivec2 setSpriteSize();
	glm::vec2 setSizeInSpriteSheet();
	void setAnimations();

private:
	int coyote, coyoteTime;
	bool bJumping, bFalling;

};


#endif // _PLAYER_INCLUDE
