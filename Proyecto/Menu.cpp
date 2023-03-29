#include "Menu.h"

#include "MenuKeyboard.h"

void Menu::init()
{
	initTextures();
	initSprites();
	mode = 0;
	modeAnterior = -1;
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

	string paths[4] = { "images/PPPlay.png", "images/OOOptions.png", "images/CCCredits.png", "images/EEExit.png"};
	for (int i = 0; i < 4; ++i) {
		textsTex[i].loadFromFile(paths[i], TEXTURE_PIXEL_FORMAT_RGBA);
		textsTex[i].setMinFilter(GL_NEAREST);
		textsTex[i].setMagFilter(GL_NEAREST);
	}
}


void Menu::initSprites()
{
	backgroundSprite = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &menuTexture, &ShaderCtrl::instance().getTexProgram()); 
	backgroundSprite->setPosition(glm::vec2(0, 0));

	nightSprite = Sprite::createSprite(glm::vec2(107, 48), glm::vec2(1.f, 1.f), &nightTexture, &ShaderCtrl::instance().getTexProgram());
	nightSprite->setPosition(glm::vec2(250, 20));

	knightSprite = Sprite::createSprite(glm::vec2(128, 48), glm::vec2(1.f, 1.f), &knightTexture, &ShaderCtrl::instance().getTexProgram());
	knightSprite->setPosition(glm::vec2(270, 70));


	//Inicializar Sprites de los textos.
	glm::vec2 sizePlay = glm::vec2(80, 40);
	int y_offset;
	float factor_size_x[4] = { 1.0f, 1.5f, 1.5f, 0.6f };
	float factor_size_y[4] = { 1.0f, 1.0f, 0.8f, 0.6f };
	int initial_anim[4] = { 1, 0, 0, 0 };
	for (int i = 0; i < 4; ++i) { 
		y_offset = i * 60;
		if (i == 3) y_offset = i * 70;
		
		texts[i] = Sprite::createSprite(glm::vec2(sizePlay.x*factor_size_x[i], sizePlay.y*factor_size_y[i]), glm::vec2(1.f, 0.5f), &textsTex[i], &ShaderCtrl::instance().getTexProgram());
		texts[i]->setPosition(glm::vec2(290, 180 + y_offset));
		
		texts[i]->setNumberAnimations(2);
		for (int j = 0; j < 2; ++j) {
			texts[i]->addKeyframe(j, positions[j]);
		}
		texts[i]->changeAnimation(initial_anim[i]);
	}
}


void Menu::update(int deltaTime)
{
	changeSprites();
}

void Menu::changeModeUp()
{
	if (mode > 0) {
		modeAnterior = mode;
		--mode;
	}

}

void Menu::changeModeDown()
{
	if (mode < 3) {
		modeAnterior = mode;
		++mode;
	}

}

void Menu::changeSprites()
{
	//switch (modeAnterior) {
	//case 0: {
	//	playSprite->changeAnimation(0);
	//	optionsSprite->changeAnimation(1);
	//	break;
	//	}
	//default:break;
	//}
	//if (mode != 0) {

	//}
	//playSprite->changeAnimation(0);
	//optionsSprite->changeAnimation(1);
	//modeAnterior = 0
	//mode = 1
	texts[mode]->changeAnimation(1);
	if (modeAnterior != -1) texts[modeAnterior]->changeAnimation(0);
}

void Menu::render()
{
	RENDER_SHADERS;
	backgroundSprite->render();
	nightSprite->render();
	knightSprite->render();
	for (int i = 0; i < 4; ++i) {
		texts[i]->render();
	}
}

