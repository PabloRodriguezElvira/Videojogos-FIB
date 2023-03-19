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
	map = TileMap::createTileMap("levels/level01.txt", glm::vec2(SCREEN_X, SCREEN_Y), TEX_PROGRAM);
}

void Scene::initPlayer()
{
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), TEX_PROGRAM);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize() - PLAYER_HITBOX_X, INIT_PLAYER_Y_TILES * map->getTileSize() - PLAYER_HITBOX_Y));
	player->setTileMap(map);
}

