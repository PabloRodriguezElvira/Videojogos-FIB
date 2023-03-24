#ifndef _VAATI_INCLUDE
#define _VAATI_INCLUDE


#include "Mob.h"


class Vaati : public Mob
{

protected:
	void initMob();
	void updateMob(int deltaTime);

	string setSpriteSheet();
	glm::ivec2 setSpriteSize();
	glm::vec2 setSizeInSpriteSheet();
	void setAnimations();

private:
	int coyote, coyoteTime;
	bool bJumping, bFalling;

};


#endif // _VAATI_INCLUDE
