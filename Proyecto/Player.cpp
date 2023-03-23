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


void Player::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	bFalling = false;
	spritesheet.loadFromFile("images/zero.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.0625, 0.1), &spritesheet, &shaderProgram);
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

	sprite->changeAnimation(STAND_RIGHT);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		posPlayer.x -= MOVE_STEP;
		bool c = map->collisionMoveLeft(posPlayer, HITBOX_SIZE);
		if (c) posPlayer.x += MOVE_STEP;

		if (bFalling)
		{
			map->paintTiles(posPlayer, HITBOX_SIZE);
			
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
			map->paintTiles(posPlayer, HITBOX_SIZE);

			if (c && sprite->animation() != STAND_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (!c && sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		posPlayer.x += MOVE_STEP;
		bool c = map->collisionMoveRight(posPlayer, HITBOX_SIZE);
		if (c) posPlayer.x -= MOVE_STEP;

		if (bFalling)
		{
			map->paintTiles(posPlayer, HITBOX_SIZE);

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
			map->paintTiles(posPlayer, HITBOX_SIZE);

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
	if(bJumping)
	{
		int newPos;
		jumpAngle += JUMP_ANGLE_STEP;

		if(jumpAngle == 180)
		{
			bJumping = false;
		}
		else if (jumpAngle <= 78)
		{
			newPos = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 156.f));
			posPlayer.y = newPos;

			if (jumpAngle == 12)
			{
				if (sprite->animation() % 2 == 0 && sprite->animation() != JUMP_LEFT)
					sprite->changeAnimation(JUMP_LEFT);
				else if (sprite->animation() % 2 == 1 && sprite->animation() != JUMP_RIGHT)
					sprite->changeAnimation(JUMP_RIGHT);
			}
		}
		else if (jumpAngle < 102)
		{
			bJumping = !map->collisionMoveDown(posPlayer, HITBOX_SIZE, &posPlayer.y);
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
			bJumping = !map->collisionMoveDown(posPlayer, HITBOX_SIZE, &posPlayer.y);
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
			newPos = int(startY - JUMP_HEIGHT * sin(3.14159f * (jumpAngle - 24) / 156.f));
			newPos <= posPlayer.y + FALL_STEP ? posPlayer.y = newPos : posPlayer.y += FALL_STEP;
			/*posPlayer.y = newPos;*/
			bJumping = !map->collisionMoveDown(posPlayer, HITBOX_SIZE, &posPlayer.y);
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
		posPlayer.y += FALL_STEP;
		bFalling = !map->collisionMoveDown(posPlayer, HITBOX_SIZE, &posPlayer.y);
		if(!bFalling)
		{
			map->paintTiles(posPlayer, HITBOX_SIZE);

			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
			else if (sprite->animation() == JUMP_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == JUMP_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}
		else
		{
			
			if (sprite->animation() % 2 == 0 && sprite->animation() != JUMP_LEFT)
				sprite->changeAnimation(JUMP_LEFT);
			else if (sprite->animation() % 2 == 1 && sprite->animation() != JUMP_RIGHT)
				sprite->changeAnimation(JUMP_RIGHT);
		}
	}
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




