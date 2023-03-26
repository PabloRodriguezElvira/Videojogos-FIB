#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "Definitions.h"


#include "State.h"
#include "Sprite.h"
#include "Texture.h"


enum Modes {play, instructions, credits};

class Menu : public State
{

public:
	static Menu &instance()
	{
		static Menu M;
		return M;
	};

	
	void init();
	void update(int deltaTime);
	void render();
	void changeMode();


private:
	void initTextures();
	void initSprites();
	void changeSprites();

	//Modos del menú:
	Modes mode;

	Texture menuTexture;
	Texture nightTexture;
	Texture knightTexture;
	Texture playTexture;
	Texture insrtuctionsTexture;
	Texture creditsTexture;

	Sprite* backgroundSprite;
	Sprite* nightSprite;
	Sprite* knightSprite;
	Sprite* playSprite;
	Sprite* instructionsSprite;
	Sprite* creditsSprite;

};


#endif // _MENU_INCLUDE