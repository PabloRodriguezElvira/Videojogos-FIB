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
	initMap();
	HUD::instance().init();
	initTextures();
	initBackground();
	initLvl();
	initPlayer();
	bPaused = false;
	initEnemies();
	currentTime = 0.0f;
	contador = 1000;
	timer = 1;
	key.init(lvl->getKeyPosition());
	keyboardCtrl = &SceneKeyboard::instance();
}


void Scene::pause() 
{
	bPaused = true;
}

void Scene::unpause()
{
	bPaused = false;
}

int Scene::getStageNum()
{
	return lvl->getStageNumber();
}

void Scene::update(int deltaTime)
{
	if (!bPaused)
	{
		currentTime += deltaTime;
		player->update(deltaTime);
		if (player->getHealth() > 0) updateEnemies(deltaTime);
		contador -= deltaTime;
		if (contador <= 0 && timer > 0) {
			timer -= 1;
			contador = 1000;
		}
		else if (timer <= 0) key.changePaint(true);
		HUD::instance().update(player->getPuntuacion(), timer);
	}
}

void Scene::render()
{
	RENDER_SHADERS;
	
	backBlack->render();
	backgSprite->render();
	ShaderCtrl::instance().setTranslateModelview();
	map->render();
	player->render();
	renderEnemies();

	HUD::instance().render();

	key.render();
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
	glm::ivec2 playerTopLeft = player->getTopLeft();
	glm::ivec2 playerBotRight = player->getBotRight();

	glm::ivec2 enemyTopLeft, enemyBotRight;

	for (Enemy* enemy : *enemies)
	{
		if (player->getHealth() > 0)
		{
			enemy->update(deltaTime);
			
			if (!player->isHurt())
			{
				enemyTopLeft = enemy->getTopLeft();
				enemyBotRight = enemy->getBotRight();

				if (!(playerBotRight.x < enemyTopLeft.x || enemyBotRight.x < playerTopLeft.x))
				{
					if (!(playerBotRight.y < enemyTopLeft.y || enemyBotRight.y < playerTopLeft.y))
					{
						player->hit();
						if (enemy->getType() != 'M') enemy->changeHorizontalDirection();
					}
				}
			}
		}
	}
}

void Scene::renderEnemies()
{
	for (Enemy* enemy : *enemies)
		enemy->render();
}

void Scene::initTextures()
{
	backgTexture.loadFromFile("images/Scene/Background/fondoPLSPLS.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backgTexture.setMinFilter(GL_NEAREST);
	backgTexture.setMagFilter(GL_NEAREST);

	backBlackTexture.loadFromFile("images/Scene/Background/fondoBlack.png", TEXTURE_PIXEL_FORMAT_RGBA);
	backBlackTexture.setMinFilter(GL_NEAREST);
	backBlackTexture.setMagFilter(GL_NEAREST);
}

void Scene::initBackground()
{
	backgSprite = Sprite::createSprite(glm::vec2((TILESIZE.x * map->getMapSize().x) - 1, TILESIZE.y * map->getMapSize().y), glm::vec2(1.f, 1.f), &backgTexture, &TEX_PROGRAM);
	backgSprite->setPosition(glm::vec2(SCREEN_X+TRANSLATE.x, SCREEN_Y+TRANSLATE.y));

	backBlack = Sprite::createSprite(glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.f, 1.f), &backBlackTexture, &TEX_PROGRAM);	
	backBlack->setPosition(glm::vec2(0,0));
}

