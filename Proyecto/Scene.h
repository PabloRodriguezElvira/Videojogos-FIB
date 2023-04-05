#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE

#include "Definitions.h"


#include "State.h"

#include "ShaderProgram.h"
#include "TileMap.h"
#include "Level.h"
#include "Player.h"
#include "Vaati.h"
#include "NumberGenerator.h"
#include "HUD.h"
#include "Key.h"
#include "Gem.h"

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
	void pause();
	void unpause();
	int getStageNum();

private:
	Scene();
	~Scene();

	void initMap();
	void initLvl();
	void initPlayer();

	void initEnemies();
	void updateEnemies(int deltaTime);
	void renderEnemies();

	void initTextures();
	void initBackground();

	void initItems();
	void renderItems();
	void updateItems(int contador);

private:
	TileMap* map;
	Level* lvl;
	Player* player;
	std::vector<Enemy*>* enemies;
	float currentTime;

	//Game background
	Texture backgTexture;
	Sprite* backgSprite;

	//Application background
	Texture backBlackTexture;
	Sprite* backBlack;

	int timer;
	int contador;

	std::vector<Item*>* items;
};


#endif // _SCENE_INCLUDE

