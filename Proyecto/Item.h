#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE

#include "Texture.h"
#include "Sprite.h"

class Item
{
public:
	void init(glm::vec2 pos);
	void initTextures();
	void render();
	void changePaint(bool b);
	bool getBPaint();
	void setPosition(glm::vec2 pos);

protected:
	virtual string getImagePath() = 0;
	virtual void initSprites() = 0;
	Texture itemTex;
	Sprite* itemSprite;
	bool bPaint;
};

#endif
