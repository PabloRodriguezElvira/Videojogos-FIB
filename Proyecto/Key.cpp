#include "Key.h"

string Key::getImagePath()
{
	return "images/Items/Key/keyy.png";
}

void Key::initSprites()
{
	this->itemSprite = Sprite::createSprite(glm::ivec2(15, 15), glm::vec2(1.f, 1.f), &itemTex, &TEX_PROGRAM);
}


