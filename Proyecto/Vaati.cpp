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
	moveStep = 1;

	hitboxSize = glm::ivec2(12, 26);
	hitboxPos = glm::ivec2(18, 22);

	transformCooldown = 12000;
	transformDuration = 2400;
	transformToWisp = false;
}

void Vaati::updateMob(int deltaTime)
{

}

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

	sprite->changeAnimation(initAnim);
}
