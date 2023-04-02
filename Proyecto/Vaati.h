#ifndef _VAATI_INCLUDE
#define _VAATI_INCLUDE


#include "Enemy.h"


class Vaati : public Enemy
{

protected:
	void initMob();
	void updateMob(int deltaTime);

	string setSpriteSheet();
	glm::ivec2 setSpriteSize();
	glm::vec2 setSizeInSpriteSheet();
	void setAnimations();

private:
	int transformCooldown, transformDuration, initWispAnim;
	bool transformToWisp;

};


#endif // _VAATI_INCLUDE
