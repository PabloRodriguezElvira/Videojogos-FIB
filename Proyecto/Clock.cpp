#include "Clock.h"

string Clock::getImagePath()
{
	return "images/Items/Clock/relojj.png";
}

void Clock::updateItem(int deltaTime)
{
	if (timeToAppear > 0) timeToAppear -= deltaTime;
	else bPaint = true;
}

void Clock::initSprites()
{
	this->itemSprite = Sprite::createSprite(glm::ivec2(15, 15), glm::vec2(1.f, 1.f), &itemTex, &TEX_PROGRAM);
}
