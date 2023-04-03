#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Player.h"

#include "Game.h"


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT
};

int Player::getPuntuacion()
{
	return this->puntuacion;
}


void Player::initMob()
{
	jumpHeight = 52;
	jumpAngleStep = 6;
	fallStep = 5;
	moveStep = 2;
	coyoteTime = 4;
	puntuacion = 0;

	hitboxSize = glm::ivec2(16, 32);
	hitboxPos = glm::ivec2(17, 26);
}

void Player::updateMob(int deltaTime)
{
	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (!Game::instance().getSpecialKey(GLUT_KEY_RIGHT) || bFalling || bJumping)
		{
			position.x -= moveStep;
			bool c = map->collisionMoveLeft(position, hitboxSize, hitboxPos);
			if (c) position.x += moveStep;

			if (bFalling)
			{
				map->paintTiles(position, hitboxSize, hitboxPos, &puntuacion);

				if (sprite->animation() != JUMP_LEFT)
					sprite->changeAnimation(JUMP_LEFT);
			}
			else if (bJumping)
			{
				if (sprite->animation() != JUMP_LEFT)
					sprite->changeAnimation(JUMP_LEFT);
			}
			else
			{
				map->paintTiles(position, hitboxSize, hitboxPos, &puntuacion);

				if (c && sprite->animation() != STAND_LEFT)
					sprite->changeAnimation(STAND_LEFT);
				else if (!c && sprite->animation() != MOVE_LEFT)
					sprite->changeAnimation(MOVE_LEFT);
			}
		}
		else
		{
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (!Game::instance().getSpecialKey(GLUT_KEY_LEFT) || bFalling || bJumping)
		{
			position.x += moveStep;
			bool c = map->collisionMoveRight(position, hitboxSize, hitboxPos);
			if (c) position.x -= moveStep;

			if (bFalling)
			{
				map->paintTiles(position, hitboxSize, hitboxPos, &puntuacion);

				if (sprite->animation() != JUMP_RIGHT)
					sprite->changeAnimation(JUMP_RIGHT);
			}
			else if (bJumping)
			{
				if (sprite->animation() != JUMP_RIGHT)
					sprite->changeAnimation(JUMP_RIGHT);
			}
			else
			{
				map->paintTiles(position, hitboxSize, hitboxPos, &puntuacion);

				if (c && sprite->animation() != STAND_RIGHT)
					sprite->changeAnimation(STAND_RIGHT);
				else if (!c && sprite->animation() != MOVE_RIGHT)
					sprite->changeAnimation(MOVE_RIGHT);
			}
		}
		else
		{
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	if (bJumping)
	{
		int newPos;
		coyote = 0;
		jumpAngle += jumpAngleStep;

		if (jumpAngle == 180)
		{
			bJumping = false;
		}
		else if (jumpAngle < 78)
		{
			newPos = int(startY - jumpHeight * sin(3.14159f * jumpAngle / 156.f));
			position.y = newPos;

			if (jumpAngle == 12)
			{
				if (sprite->animation() % 2 == 0 && sprite->animation() != JUMP_LEFT)
					sprite->changeAnimation(JUMP_LEFT);
				else if (sprite->animation() % 2 == 1 && sprite->animation() != JUMP_RIGHT)
					sprite->changeAnimation(JUMP_RIGHT);
			}
			if (map->collisionMoveUp(position, hitboxSize, hitboxPos, &position.y, fallStep))
			{
				startY = position.y + jumpHeight;
				jumpAngle = 78;
			}
		}


		else if (jumpAngle == 78)
		{
			newPos = int(startY - jumpHeight);
			position.y = newPos;
		}
		else if (jumpAngle < 102)
		{
			bJumping = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
			if (!bJumping)
			{
				if (sprite->animation() % 2 == 0)
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() % 2 == 1)
					sprite->changeAnimation(STAND_RIGHT);
			}
		}

		else if (jumpAngle == 102)
		{
			bJumping = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
			bFalling = bJumping;
			if (!bJumping)
			{
				if (sprite->animation() % 2 == 0)
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() % 2 == 1)
					sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else
		{
			newPos = int(startY - jumpHeight * sin(3.14159f * (jumpAngle - 24) / 156.f));
			newPos <= position.y + fallStep ? position.y = newPos : position.y += fallStep;
			/*position.y = newPos;*/
			bJumping = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
			if (!bJumping)
			{
				if (sprite->animation() % 2 == 0)
					sprite->changeAnimation(STAND_LEFT);
				else if (sprite->animation() % 2 == 1)
					sprite->changeAnimation(STAND_RIGHT);
			}
		}
	}
	else
	{
		position.y += fallStep;
		bFalling = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
		if (!bFalling)
		{
			map->paintTiles(position, hitboxSize, hitboxPos, &puntuacion);

			coyote = coyoteTime;

			if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !map->collisionMoveUp(glm::ivec2(position.x, position.y - 1), hitboxSize, hitboxPos, &position.y, fallStep))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = position.y;
			}
			else if (sprite->animation() == JUMP_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == JUMP_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
		else
		{
			if (coyote) {
				position.y -= fallStep + coyote - coyoteTime;
				coyote -= 1;
				if (Game::instance().getSpecialKey(GLUT_KEY_UP) && !map->collisionMoveUp(glm::ivec2(position.x, position.y - 1), hitboxSize, hitboxPos, &position.y, fallStep))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = position.y;
				}
			}
			if (sprite->animation() % 2 == 0 && sprite->animation() != JUMP_LEFT)
				sprite->changeAnimation(JUMP_LEFT);
			else if (sprite->animation() % 2 == 1 && sprite->animation() != JUMP_RIGHT)
				sprite->changeAnimation(JUMP_RIGHT);
		}
	}
}

string Player::setSpriteSheet()
{
	return "images/zero.png";
}

glm::ivec2 Player::setSpriteSize()
{
	return glm::ivec2(64, 64);
}

glm::vec2 Player::setSizeInSpriteSheet()
{
	return glm::vec2(0.0625, 0.1);
}

void Player::setAnimations()
{
	sprite->setNumberAnimations(8);

	int i;
	sprite->setAnimationSpeed(STAND_RIGHT, 8);
	for (i = 0; i < 11; ++i)
		sprite->addKeyframe(STAND_RIGHT, glm::vec2((float(i) * 0.0625f), 0.0f));

	sprite->setAnimationSpeed(STAND_LEFT, 8);
	for (i = 0; i < 11; ++i)
		sprite->addKeyframe(STAND_LEFT, glm::vec2((float(i) * 0.0625f), 0.1f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 10);
	for (i = 0; i < 8; ++i)
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2((float(i) * 0.0625f), 0.2f));

	sprite->setAnimationSpeed(MOVE_LEFT, 10);
	for (i = 0; i < 8; ++i)
		sprite->addKeyframe(MOVE_LEFT, glm::vec2((float(i) * 0.0625f), 0.3f));

	sprite->setAnimationSpeed(JUMP_RIGHT, 10);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2((float(i) * 0.0625f), 0.4f));

	sprite->setAnimationSpeed(JUMP_LEFT, 10);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(JUMP_LEFT, glm::vec2((float(i) * 0.0625f), 0.5f));

	sprite->changeAnimation(initAnim);
}
