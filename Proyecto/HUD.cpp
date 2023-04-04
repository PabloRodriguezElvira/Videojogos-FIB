#include "HUD.h"


void HUD::init()
{
	NumberGenerator::instance().initTexture();
	numVidas.init();
	puntuacion.init(6);
	tiempo.init(2);
	stage.init();
	setAllPositions();
}

void HUD::update(int punt, int timer)
{
	numVidas.displayVidas(9);
	puntuacion.displayNum(punt);
	tiempo.displayNum(timer);
	stage.displayLevel(Scene::instance().getStageNum());
}

void HUD::render()
{	
	numVidas.render();
	puntuacion.render();
	tiempo.render();
	stage.render();
}

void HUD::setAllPositions()
{
	numVidas.setPosition(glm::vec2(20, 25));
	puntuacion.setPosition(glm::vec2(120, 25));
	tiempo.setPosition(glm::vec2(300, 25));
	stage.setPosition(glm::vec2(450, 25));
}


