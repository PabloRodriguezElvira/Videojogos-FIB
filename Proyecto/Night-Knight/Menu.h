#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "SpriteManager.h"
#include "Sprite.h"
#include "Game.h"
#include "ShaderProgram.h"

class Menu : public StateManager
{
public:
	Menu();
	~Menu();
	void init();
	void update(int deltaTime);
	void render();

private:
	void initTextures();
	
	Texture menuTexture;
	Sprite* menuBackground;
};

#endif

