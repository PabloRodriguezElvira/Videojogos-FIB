#include "VidasDisplay.h"

void VidasDisplay::init()
{
	initTextures();
	numV = NumberGenerator::instance().createNum();
	heart = Sprite::createSprite(glm::ivec2(25, 25), glm::vec2(1.f, 1.f), &heartTex, &TEX_PROGRAM);
	cross = Sprite::createSprite(glm::ivec2(15, 15), glm::vec2(1.f, 1.f), &crossTex, &TEX_PROGRAM);
}

void VidasDisplay::initTextures()
{	
	heartTex.loadFromFile("images/HUD/Vidas/cora.png", TEXTURE_PIXEL_FORMAT_RGBA);
	heartTex.setMinFilter(GL_NEAREST);
	heartTex.setMagFilter(GL_NEAREST);

	crossTex.loadFromFile("images/HUD/Vidas/cross.png", TEXTURE_PIXEL_FORMAT_RGBA);
	crossTex.setMinFilter(GL_NEAREST);
	crossTex.setMagFilter(GL_NEAREST);	
}

void VidasDisplay::displayVidas(int num)
{
	numV->changeAnimation(num);
}

void VidasDisplay::render()
{
	heart->render();
	cross->render();
	numV->render();
}

void VidasDisplay::setPosition(glm::vec2 pos)
{
	heart->setPosition(pos);
	cross->setPosition(pos + glm::vec2(30, 10));
	numV->setPosition(pos + glm::vec2(50, 3));
}

