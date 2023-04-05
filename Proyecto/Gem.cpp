#include "Gem.h"

string Gem::getImagePath()
{
	return "images/Items/Gem/gemita.png";
}

void Gem::updateItem(int deltaTime)
{
	if (timeToAppear > 0) timeToAppear -= deltaTime;
	else bPaint = true;
}

void Gem::initSprites()
{
	this->itemSprite = Sprite::createSprite(glm::ivec2(12, 16), glm::vec2(0.1f, 1.f), &itemTex, &TEX_PROGRAM);

	this->itemSprite->setNumberAnimations(1);
	this->itemSprite->setAnimationSpeed(0, 4);
	for (int i = 0; i < 9; ++i) {
		this->itemSprite->addKeyframe(0, glm::vec2(0.1f*float(i), 0));
	}
	this->itemSprite->changeAnimation(0);
}
