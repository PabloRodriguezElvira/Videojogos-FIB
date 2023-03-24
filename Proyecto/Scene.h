#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include "Definitions.h"


#include "State.h"

#include "ShaderProgram.h"
#include "TileMap.h"
#include "Level.h"
#include "Player.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene : public State
{

public:
	static Scene &instance()
	{
		static Scene S;
		return S;
	}

	void init();
	void update(int deltaTime);
	void render();

private:
	Scene();
	~Scene();

	void initMap();
	void initLvl();
	void initPlayer();

private:
	TileMap *map;
	Level* lvl;
	Player *player;
	float currentTime;

};


#endif // _SCENE_INCLUDE

