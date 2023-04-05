#include "Item.h"
#include <iostream>

void Item::init()
{
	initTextures();
	initSprites();
	setPosition();
	bPaint = false;
}

void Item::setInitialTile(glm::vec2 pos)
{
	this->initTile = pos;
}

void Item::setPosition()
{
	glm::vec2 pos = glm::vec2(SCREEN_X + initTile.x * TILESIZE.x, SCREEN_Y + initTile.y * TILESIZE.y);
	pos = pos + glm::vec2(TRANSLATE.x, TRANSLATE.y) - glm::vec2(0, TILESIZE.y);
	this->itemSprite->setPosition(pos);
}

bool Item::getBPaint()
{
	return bPaint;
}

void Item::initTextures()
{	
	itemTex.loadFromFile(getImagePath(), TEXTURE_PIXEL_FORMAT_RGBA);
	itemTex.setMinFilter(GL_NEAREST);
	itemTex.setMagFilter(GL_NEAREST);
}

void Item::render()
{
	if (bPaint) itemSprite->render();
}

void Item::update(int deltaTime)
{
	updateItem(deltaTime);
	itemSprite->update(deltaTime);
}

void Item::changeBPaint(bool b)
{
	bPaint = b;
}
