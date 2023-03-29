#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Scene.h"

#include "SceneKeyboard.h"
#include "Game.h"


Scene::Scene()
{
	map = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void Scene::init()
{
	initBackground();
	initMap();
	initLvl();
	initPlayer();
	initEnemies();
		
	currentTime = 0.0f;
	keyboardCtrl = &SceneKeyboard::instance();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	//updateEnemies(deltaTime);
}

void Scene::render()
{
	RENDER_SHADERS;

	backgSprite->render();
	ShaderCtrl::instance().setTranslateModelview();
	map->render();
	player->render();
	renderEnemies();
}


void Scene::initMap()
{
	map = TileMap::createTileMap("levels/tilemap01.txt", glm::vec2(SCREEN_X, SCREEN_Y), TEX_PROGRAM);
}

void Scene::initLvl()
{
	lvl = Level::createLevel("levels/level01.txt");
}

void Scene::initPlayer()
{
	player = new Player();
	player->init(map, glm::ivec2(SCREEN_X + TRANSLATE.x, SCREEN_Y + TRANSLATE.y),
				 glm::ivec2(map->getTileSizeX() * lvl->getInitPlayerPosX(), map->getTileSizeY() * lvl->getInitPlayerPosY()),
				 lvl->getInitPlayerAnim(), TEX_PROGRAM);
}

void Scene::initEnemies()
{
	enemies = lvl->getEnemies();
	for (Enemy* enemy : *enemies)
		enemy->init(map, glm::ivec2(SCREEN_X + TRANSLATE.x, SCREEN_Y + TRANSLATE.y),
					glm::ivec2(map->getTileSizeX() * enemy->getInitTileX(), map->getTileSizeY() * enemy->getInitTileY()),
					enemy->getInitAnim(), TEX_PROGRAM);
}

void Scene::updateEnemies(int deltaTime)
{
	for (Enemy* enemy : *enemies)
	{
		enemy->update(deltaTime);
	}
}

void Scene::renderEnemies()
{
	for (Enemy* enemy : *enemies)
		enemy->render();
}

void Scene::initBackground()
{
	spritesheet.loadFromFile("images/fondoPLSPLS.png", TEXTURE_PIXEL_FORMAT_RGBA);
	spritesheet.setMinFilter(GL_NEAREST);
	spritesheet.setMagFilter(GL_NEAREST);

	backgSprite = Sprite::createSprite(glm::vec2((TILESIZE.x * TILES.x) - 1, TILESIZE.y * TILES.y), glm::vec2(1.f, 1.f), &spritesheet, &TEX_PROGRAM);
	backgSprite->setPosition(glm::vec2(SCREEN_X+TRANSLATE.x, SCREEN_Y+TRANSLATE.y));
}

