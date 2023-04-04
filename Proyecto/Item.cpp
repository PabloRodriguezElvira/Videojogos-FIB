#include "Item.h"

void Item::init(glm::vec2 posTile)
{
	initTextures();
	initSprites();
	glm::vec2 pos = glm::vec2(SCREEN_X + posTile.x * TILESIZE.x, SCREEN_Y + posTile.y * TILESIZE.y);
	setPosition(pos + glm::vec2(TRANSLATE.x, TRANSLATE.y) - glm::vec2(0, TILESIZE.y));
	bPaint = false;
}

void Item::setPosition(glm::vec2 pos)
{
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

void Item::changePaint(bool b)
{
	bPaint = b;
}
