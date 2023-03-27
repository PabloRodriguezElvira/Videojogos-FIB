#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "Definitions.h"


#include "State.h"
#include "Sprite.h"
#include "Texture.h"


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
	void changeModeUp();
	void changeModeDown();


private:
	void initTextures();
	void initSprites();
	void changeSprites();

	//Modos del menú:
	int mode;

	Texture menuTexture;
	Texture nightTexture;
	Texture knightTexture;
	Texture playTexture;
	Texture optionsTexture;
	Texture creditsTexture;

	Sprite* backgroundSprite;
	Sprite* nightSprite;
	Sprite* knightSprite;
	Sprite* texts[3];

	//Positions for text sprites:
	glm::vec2 positions[2] = {
		glm::vec2(0.f, 0.f),
		glm::vec2(0.f, 0.5f)
	};

};


#endif // _MENU_INCLUDE