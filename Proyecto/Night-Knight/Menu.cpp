#include "Menu.h"
#include "Game.h"
#include "ShaderProgram.h"

Menu::Menu() {}

Menu::~Menu() {}

void Menu::init()
{
	initTextures();
	menuBackground = Sprite::createSprite(glm::vec2(1024, 1024), glm::vec2(1.f, 1.f), &menuTexture, NULL);
}

void Menu::initTextures()
{
	menuTexture.loadFromFile("images/aaa.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuTexture.setMinFilter(GL_NEAREST);
	menuTexture.setMagFilter(GL_NEAREST);
}
