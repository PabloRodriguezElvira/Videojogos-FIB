#include "HUD.h"


void HUD::init()
{
	NumberGenerator::instance().initTexture();
	numVidas.init();
	puntuacion.init(6);
	time.init(2);
	stage.init();
	setAllPositions();
}

void HUD::update(int punt)
{
	//Pillar:
	//Vidas -> Player
	numVidas.displayVidas(9);
	puntuacion.displayNum(punt);
	time.displayNum(60);
	stage.displayLevel(69);
	//Puntuacion -> Player
	//Stage -> Level
	//Tiempo -> Scene
}

void HUD::render()
{	
	numVidas.render();
	puntuacion.render();
	time.render();
	stage.render();
}

void HUD::setAllPositions()
{
	numVidas.setPosition(glm::vec2(20, 25));
	puntuacion.setPosition(glm::vec2(120, 25));
	time.setPosition(glm::vec2(300, 25));
	stage.setPosition(glm::vec2(450, 25));
}


