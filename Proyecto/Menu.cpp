#include "Menu.h"

#include "MenuKeyboard.h"

void Menu::init()
{
	initTextures();
	initSprites();
	currentTime = 0.f;
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

	playTexture.loadFromFile("images/PPPlay.png", TEXTURE_PIXEL_FORMAT_RGBA);
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

	texts[0] = Sprite::createSprite(glm::vec2(SCREEN_WIDTH / 8.f, SCREEN_HEIGHT / 18.f), glm::vec2(1.f, 0.5f), &playTexture, &ShaderCtrl::instance().getTexProgram());
	texts[0]->setPosition(glm::vec2(290, SCREEN_HEIGHT / 3.f + 20));
	
	texts[0]->setNumberAnimations(2);
	for (int i = 0; i < 2; ++i) {
		texts[0]->addKeyframe(i, positions[i]);
	}
	texts[0]->changeAnimation(1);
}


void Menu::update(int deltaTime)
{
	changeSprites();
}

void Menu::changeModeUp()
{
	if (mode < 3) ++mode;
}

void Menu::changeModeDown()
{
	if (mode >= 0) --mode;	
}

void Menu::changeSprites()
{
	//if (mode < 3) {
	//	texts[mode]->changeAnimation(0);
	//	texts[mode+1]->changeAnimation(1);
	//}
}

void Menu::render()
{
	RENDER_SHADERS;
	backgroundSprite->render();
	nightSprite->render();
	knightSprite->render();
	for (int i = 0; i < 3; ++i) texts[i]->render();
}

