#include "Menu.h"

#include "MenuKeyboard.h"

void Menu::init()
{
	initTextures();
	initSprites();
	mode = play;
	keyboardCtrl = &MenuKeyboard::instance();
}

void Menu::initTextures()
{
	menuTexture.loadFromFile("images/fondo_noche.png", TEXTURE_PIXEL_FORMAT_RGBA);
	menuTexture.setMinFilter(GL_NEAREST);
	menuTexture.setMagFilter(GL_NEAREST);

	nightTexture.loadFromFile("images/nightWhite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	nightTexture.setMinFilter(GL_NEAREST);
	nightTexture.setMagFilter(GL_NEAREST);

	knightTexture.loadFromFile("images/knightWhite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	knightTexture.setMinFilter(GL_NEAREST);
	knightTexture.setMagFilter(GL_NEAREST);

	playTexture.loadFromFile("images/playWhite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	playTexture.setMinFilter(GL_NEAREST);
	playTexture.setMagFilter(GL_NEAREST);
}


void Menu::initSprites()
{
	backgroundSprite = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &menuTexture, &ShaderCtrl::instance().getTexProgram()); 
	backgroundSprite->setPosition(glm::vec2(0, 0));

	nightSprite = Sprite::createSprite(glm::vec2(SCREEN_WIDTH/6.f, SCREEN_HEIGHT/10.f), glm::vec2(1.f, 1.f), &nightTexture, &ShaderCtrl::instance().getTexProgram());
	nightSprite->setPosition(glm::vec2(250, 20));

	knightSprite = Sprite::createSprite(glm::vec2(SCREEN_WIDTH/5.f, SCREEN_HEIGHT/10.f), glm::vec2(1.f, 1.f), &knightTexture, &ShaderCtrl::instance().getTexProgram());
	knightSprite->setPosition(glm::vec2(270, SCREEN_HEIGHT/10.f + 22));

	//Cambiar esto. Añadir animations y tal.
	playSprite = Sprite::createSprite(glm::vec2(SCREEN_WIDTH/5.f, SCREEN_HEIGHT/10.f), glm::vec2(1.f, 1.f), &playTexture, &ShaderCtrl::instance().getTexProgram());
	playSprite->setPosition(glm::vec2(270, SCREEN_HEIGHT/3.f));
}


void Menu::update(int deltaTime)
{
	changeSprites();
}

void Menu::changeMode()
{
	switch (mode) {
		case play: mode = instructions; break;
		case instructions: mode = credits; break;
		default: mode = play;
	}
}

void Menu::changeSprites()
{
	int modeNum = 1;
	//Transformar mode (enum) en número.
	if (mode == play) playSprite->changeAnimation(modeNum);
	else if (mode == instructions) instructionsSprite->changeAnimation(modeNum);
	else creditsSprite->changeAnimation(modeNum);
}

void Menu::render()
{
	RENDER_SHADERS;
	backgroundSprite->render();
	nightSprite->render();
	knightSprite->render();
	playSprite->render();
}

