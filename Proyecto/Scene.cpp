#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Scene.h"

#include "SceneKeyboard.h"
#include "ShaderCtrl.h"
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
	initMap();
	initLvl();
	initPlayer();
	
	currentTime = 0.0f;
	keyboardCtrl = &SceneKeyboard::instance();
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
}

void Scene::render()
{
	RENDER_SHADERS;

	map->render();
	player->render();
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
	player->init(map, lvl, glm::ivec2(SCREEN_X, SCREEN_Y), TEX_PROGRAM);
}

