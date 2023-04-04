#ifndef _INFO_INCLUDE 
#define _INFO_INCLUDE

#include "Definitions.h"

#include "State.h"
#include "Sprite.h"
#include "Texture.h"
#include "InfoKeyboard.h"

class Info: public State
{	
public:
	static Info &instance()
	{
		static Info I;
		return I;
	};
	
	void update(int deltaTime);
	void init();
	void render();
	void pause();
	void unpause();

	void setMode(int mode);

private:
	void initTextures();
	void initSprites();

	Texture imageTexture;
	int mode; //1->Options, 2->Credits

	Sprite* imageSprite;
}; 

#endif // _INFO_INCLUDE

