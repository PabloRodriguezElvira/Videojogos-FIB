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
public:
	int getHealth() { return health; }
	bool isHurt() { return hurt; }

	void hit();

protected:
	void initMob();
	void updateMob(int deltaTime);
	void updateHurt(int deltaTime);
	void updateMovement();

	string setSpriteSheet();
	glm::ivec2 setSpriteSize();
	glm::vec2 setSizeInSpriteSheet();
	void setAnimations();

private:
	int coyote, coyoteTime, health, hurtTime, blink;
	bool bJumping, bFalling, hurt, reset;

};


#endif // _PLAYER_INCLUDE
