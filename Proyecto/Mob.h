#ifndef _MOB_INCLUDE
#define _MOB_INCLUDE

#include "Definitions.h"


#include "Sprite.h"
#include "TileMap.h"
#include "TileMap.h"
#include "Level.h"


class Mob
{

public:
	void init(TileMap* tileMap, Level* level, const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

protected:
	virtual void initMob() = 0;
	virtual void updateMob(int deltaTime) = 0;

	void setPosition(const glm::ivec2& pos);
	virtual string setSpriteSheet() = 0;
	virtual glm::ivec2 setSpriteSize() = 0;
	virtual glm::vec2 setSizeInSpriteSheet() = 0;
	virtual void setAnimations() = 0;

protected:
	int startY, jumpHeight, jumpAngle, jumpAngleStep, fallStep, moveStep, coyoteTime;
	glm::ivec2 tileMapDispl, position, hitboxSize, hitboxPos;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	Level *lvl;
};


#endif // _MOB_INCLUDE