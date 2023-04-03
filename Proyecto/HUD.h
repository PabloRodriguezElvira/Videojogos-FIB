#ifndef _HUD_INCLUDE
#define _HUD_INCLUDE

#include "Sprite.h"
#include "NumberGenerator.h"
#include "VidasDisplay.h"
#include "PuntuacionDisplay.h"
#include "StageDisplay.h"

class HUD
{

public:
	static HUD& instance()
	{
		static HUD instance; 
		return instance;
	};

	void init();
	void update(int punt);
	void render();

	void setAllPositions();

	//int getButtonIndexInPos(int posX, int posY);
	//void changeSelectedButton(int selectedButton);
	//int getSelectedButtonJobCount();

	//void changeDisplayedJob(string lemmingJobName);
private:
	VidasDisplay numVidas;
	PuntuacionDisplay puntuacion;
	PuntuacionDisplay time;
	StageDisplay stage;
};
#endif //_HUD_INCLUDE

