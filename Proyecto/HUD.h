#ifndef _HUD_INCLUDE
#define _HUD_INCLUDE


#include "Scene.h"
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
	void update(int punt, int timer);
	void render();

	void setAllPositions();

private:
	VidasDisplay numVidas;
	PuntuacionDisplay puntuacion;
	PuntuacionDisplay tiempo;
	StageDisplay stage;
};
#endif //_HUD_INCLUDE

