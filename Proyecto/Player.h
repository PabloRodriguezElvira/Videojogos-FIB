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
	void hit();
	void flipGodMode() { godMode = !godMode; }
	void takeItem(char item);

	int getHealth() { return health; }
	bool isHurt() { return hurt; }
	bool isGodMode() { return godMode; }
	bool hasKey() { return key; }
	bool hasClock() { return clock; }
	bool hasWon() { return win; }

public:
	int getPuntuacion();

protected:
	void initMob();
	void updateMob(int deltaTime);
	void updateHurt(int deltaTime);
	void updateMovement();
	void updateStats(int deltaTime);

	string setSpriteSheet();
	glm::ivec2 setSpriteSize();
	glm::vec2 setSizeInSpriteSheet();
	void setAnimations();

private:
	int coyote, coyoteTime, puntuacion, puntGoal, health, hurtTime, blink, clockTime;
	bool bJumping, bFalling, hurt, reset, godMode, key, clock, win;

};


#endif // _PLAYER_INCLUDE
