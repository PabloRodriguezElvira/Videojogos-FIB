#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Vaati.h"
#include "Game.h"


enum PlayerAnims
{
	MOVE_LEFT, MOVE_RIGHT, TRANSFORMATION
};


void Vaati::initMob()
{
	jumpHeight = 52;
	jumpAngleStep = 6;
	fallStep = 5;
	moveStep = 2;
	coyoteTime = 4;

	hitboxSize = glm::ivec2(12, 26);
	hitboxPos = glm::ivec2(18, 22);
}

void Vaati::updateMob(int deltaTime)
{

}

//void Vaati::updateMob(int deltaTime)
//{
//	if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
//	{
//		if (!Game::instance().getSpecialKey(GLUT_KEY_RIGHT) || bFalling || bJumping)
//		{
//			position.x -= moveStep;
//			bool c = map->collisionMoveLeft(position, hitboxSize, hitboxPos);
//			if (c) position.x += moveStep;
//
//			if (bFalling)
//			{
//				map->paintTiles(position, hitboxSize, hitboxPos);
//
//				if (sprite->animation() != JUMP_LEFT)
//					sprite->changeAnimation(JUMP_LEFT);
//			}
//			else if (bJumping)
//			{
//				if (sprite->animation() != JUMP_LEFT)
//					sprite->changeAnimation(JUMP_LEFT);
//			}
//			else
//			{
//				map->paintTiles(position, hitboxSize, hitboxPos);
//
//				if (c && sprite->animation() != STAND_LEFT)
//					sprite->changeAnimation(STAND_LEFT);
//				else if (!c && sprite->animation() != MOVE_LEFT)
//					sprite->changeAnimation(MOVE_LEFT);
//			}
//		}
//		else
//		{
//			if (sprite->animation() == MOVE_LEFT)
//				sprite->changeAnimation(STAND_LEFT);
//			else if (sprite->animation() == MOVE_RIGHT)
//				sprite->changeAnimation(STAND_RIGHT);
//		}
//	}
//	else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
//	{
//		if (!Game::instance().getSpecialKey(GLUT_KEY_LEFT) || bFalling || bJumping)
//		{
//			position.x += moveStep;
//			bool c = map->collisionMoveRight(position, hitboxSize, hitboxPos);
//			if (c) position.x -= moveStep;
//
//			if (bFalling)
//			{
//				map->paintTiles(position, hitboxSize, hitboxPos);
//
//				if (sprite->animation() != JUMP_RIGHT)
//					sprite->changeAnimation(JUMP_RIGHT);
//			}
//			else if (bJumping)
//			{
//				if (sprite->animation() != JUMP_RIGHT)
//					sprite->changeAnimation(JUMP_RIGHT);
//			}
//			else
//			{
//				map->paintTiles(position, hitboxSize, hitboxPos);
//
//				if (c && sprite->animation() != STAND_RIGHT)
//					sprite->changeAnimation(STAND_RIGHT);
//				else if (!c && sprite->animation() != MOVE_RIGHT)
//					sprite->changeAnimation(MOVE_RIGHT);
//			}
//		}
//		else
//		{
//			if (sprite->animation() == MOVE_LEFT)
//				sprite->changeAnimation(STAND_LEFT);
//			else if (sprite->animation() == MOVE_RIGHT)
//				sprite->changeAnimation(STAND_RIGHT);
//		}
//	}
//	else
//	{
//		if (sprite->animation() == MOVE_LEFT)
//			sprite->changeAnimation(STAND_LEFT);
//		else if (sprite->animation() == MOVE_RIGHT)
//			sprite->changeAnimation(STAND_RIGHT);
//	}
//	if (bJumping)
//	{
//		int newPos;
//		coyote = 0;
//		jumpAngle += jumpAngleStep;
//
//		if (jumpAngle == 180)
//		{
//			bJumping = false;
//		}
//		else if (jumpAngle < 78)
//		{
//			newPos = int(startY - jumpHeight * sin(3.14159f * jumpAngle / 156.f));
//			position.y = newPos;
//
//			if (jumpAngle == 12)
//			{
//				if (sprite->animation() % 2 == 0 && sprite->animation() != JUMP_LEFT)
//					sprite->changeAnimation(JUMP_LEFT);
//				else if (sprite->animation() % 2 == 1 && sprite->animation() != JUMP_RIGHT)
//					sprite->changeAnimation(JUMP_RIGHT);
//			}
//			if (map->collisionMoveUp(position, hitboxSize, hitboxPos, &position.y, fallStep))
//			{
//				startY = position.y + jumpHeight;
//				jumpAngle = 78;
//			}
//		}
//
//
//		else if (jumpAngle == 78)
//		{
//			newPos = int(startY - jumpHeight);
//			position.y = newPos;
//		}
//		else if (jumpAngle < 102)
//		{
//			bJumping = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
//			if (!bJumping)
//			{
//				if (sprite->animation() % 2 == 0)
//					sprite->changeAnimation(STAND_LEFT);
//				else if (sprite->animation() % 2 == 1)
//					sprite->changeAnimation(STAND_RIGHT);
//			}
//		}
//
//		else if (jumpAngle == 102)
//		{
//			bJumping = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
//			bFalling = bJumping;
//			if (!bJumping)
//			{
//				if (sprite->animation() % 2 == 0)
//					sprite->changeAnimation(STAND_LEFT);
//				else if (sprite->animation() % 2 == 1)
//					sprite->changeAnimation(STAND_RIGHT);
//			}
//		}
//		else
//		{
//			newPos = int(startY - jumpHeight * sin(3.14159f * (jumpAngle - 24) / 156.f));
//			newPos <= position.y + fallStep ? position.y = newPos : position.y += fallStep;
//			/*position.y = newPos;*/
//			bJumping = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
//			if (!bJumping)
//			{
//				if (sprite->animation() % 2 == 0)
//					sprite->changeAnimation(STAND_LEFT);
//				else if (sprite->animation() % 2 == 1)
//					sprite->changeAnimation(STAND_RIGHT);
//			}
//		}
//	}
//	else
//	{
//		position.y += fallStep;
//		bFalling = !map->collisionMoveDown(position, hitboxSize, hitboxPos, &position.y, fallStep);
//		if (!bFalling)
//		{
//			map->paintTiles(position, hitboxSize, hitboxPos);
//			coyote = coyoteTime;
//
//			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
//			{
//				bJumping = true;
//				jumpAngle = 0;
//				startY = position.y;
//			}
//			else if (sprite->animation() == JUMP_LEFT)
//				sprite->changeAnimation(STAND_LEFT);
//			else if (sprite->animation() == JUMP_RIGHT)
//				sprite->changeAnimation(STAND_RIGHT);
//		}
//		else
//		{
//			if (coyote) {
//				position.y -= coyote + (fallStep - coyoteTime);
//				coyote -= 1;
//				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
//				{
//					bJumping = true;
//					jumpAngle = 0;
//					startY = position.y;
//				}
//			}
//			if (sprite->animation() % 2 == 0 && sprite->animation() != JUMP_LEFT)
//				sprite->changeAnimation(JUMP_LEFT);
//			else if (sprite->animation() % 2 == 1 && sprite->animation() != JUMP_RIGHT)
//				sprite->changeAnimation(JUMP_RIGHT);
//		}
//	}
//}

string Vaati::setSpriteSheet()
{
	return "images/vaati2.png";
}

glm::ivec2 Vaati::setSpriteSize()
{
	return glm::ivec2(48, 48);
}

glm::vec2 Vaati::setSizeInSpriteSheet()
{
	return glm::vec2(0.0625, 0.125);
}

void Vaati::setAnimations()
{
	sprite->setNumberAnimations(3);

	int i;
	sprite->setAnimationSpeed(MOVE_RIGHT, 10);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2((float(i) * 0.0625f), 0.0f));

	sprite->setAnimationSpeed(MOVE_LEFT, 10);
	for (i = 0; i < 4; ++i)
		sprite->addKeyframe(MOVE_LEFT, glm::vec2((float(i) * 0.0625f), 0.125f));

	sprite->setAnimationSpeed(TRANSFORMATION, 10);
	for (i = 0; i < 12; ++i)
		sprite->addKeyframe(TRANSFORMATION, glm::vec2((float(i) * 0.0625f), 0.25f));
	for (i = 0; i < 12; ++i)
		sprite->addKeyframe(TRANSFORMATION, glm::vec2((float(i) * 0.0625f), 0.375f));

	sprite->changeAnimation(TRANSFORMATION);
}
