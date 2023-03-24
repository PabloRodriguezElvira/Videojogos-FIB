#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>

#include "Mob.h"

#include "Game.h"


void Mob::init(TileMap* tileMap, Level* level, const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	spritesheet.loadFromFile(setSpriteSheet(), TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(setSpriteSize(), setSizeInSpriteSheet(), &spritesheet, &shaderProgram);
	setAnimations();
	tileMapDispl = tileMapPos;
	map = tileMap;
	lvl = level;
	initMob();
	setPosition(glm::ivec2(map->getTileSizeX() *  lvl->getInitPlayerPosX() - hitboxPos.x, map->getTileSizeY() * lvl->getInitPlayerPosY() - hitboxPos.y - hitboxSize.y));
}

void Mob::update(int deltaTime)
{
	sprite->update(deltaTime);
	updateMob(deltaTime);
	setPosition(position);
}

void Mob::render()
{
	sprite->render();
}

void Mob::setPosition(const glm::ivec2& pos)
{
	position = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}

