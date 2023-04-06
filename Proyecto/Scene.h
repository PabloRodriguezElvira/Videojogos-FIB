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

	void pause() { bPaused = true; }
	void unpause() { bPaused = false; }

	void flipGodMode();
	void changeStage(int s) { stage = s; }

	int getStage() { return stage; }

private:
	Scene();
	~Scene();

	void initMap();
	void initLvl();
	void initPlayer();

	void initEnemies();
	void updateEnemies(int deltaTime);
	void renderEnemies();
	void unpaintEnemies();

	void initItems();
	void updateItems(int contador);
	void renderItems();
	void unpaintItems();

	void initHUD();
	void updateTimer(int deltaTime);

	void initTextures();
	void initBackground();

private:
	TileMap* map;
	Level* lvl;
	Player* player;
	std::vector<Enemy*>* enemies;
	std::vector<Item*>* items;
	float currentTime;

	//Game background
	Texture backgTexture;
	Sprite* backgSprite;

	//Application background
	Texture backBlackTexture;
	Sprite* backBlack;

	//Ready:
	Texture readyTex;
	Sprite* readySprite;

	//Game Over: 
	Texture gameOverTex;
	Sprite* gameOverSprite;

	int stage = 0;
	int pauseDuration, timer, timerCooldown, deathDuration, gameOverDuration;

	bool gameOver, musicChanged;

};


#endif // _SCENE_INCLUDE

