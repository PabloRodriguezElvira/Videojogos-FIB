#ifndef _ITEM_INCLUDE
#define _ITEM_INCLUDE

#include "Texture.h"
#include "Sprite.h"

class Item
{
public:
	void init();
	void initTextures();
	void render();
	void update(int deltaTime);
	void changeBPaint(bool b);
	bool getBPaint();
	void setInitialTile(glm::vec2 tile);
	void setPosition();
	void setType(char type) { this->type = type; }
	char getType() const { return this->type; }
	void setTimeToAppear(int time) { this->timeToAppear = time*1000; }
	int getTimeToAppear() const { return timeToAppear; }

protected:
	virtual string getImagePath() = 0;
	virtual void initSprites() = 0;
	virtual void updateItem(int deltaTime) { ; }
	Texture itemTex;
	Sprite* itemSprite;
	bool bPaint;
	glm::vec2 initTile;
	char type;
	int timeToAppear;
};

#endif
