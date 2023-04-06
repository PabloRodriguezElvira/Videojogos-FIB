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
	if (stage == 0) stage = 1;

	SoundCtrl::instance().putTrack("sounds/Scene/VaatiTheme.mp3", 0.1f);

	initMap();
	initTextures();
	initBackground();

	initLvl();
	initPlayer();
	initEnemies();
	
	bPaused = true;
	pauseDuration = 2800;

	currentTime = 0.0f;
	timerCooldown = 1000;
	timer = 60;
	initHUD();
	initItems();

	keyboardCtrl = &SceneKeyboard::instance();
}

void Scene::update(int deltaTime)
{
	if (!bPaused)
	{
		currentTime += deltaTime;
		player->update(deltaTime);
		updateItems(deltaTime);
		updateEnemies(deltaTime);
		if (!player->hasClock()) updateTimer(deltaTime);
		HUD::instance().update(player->getHealth(), player->getPuntuacion(), timer, stage);
		
		if (player->getHealth() == 0)
		{
			player->unpaint();
			unpaintEnemies();
			unpaintItems();
			bPaused = true;
			pauseDuration = 4000;
		}
	}
	else
	{
		if (pauseDuration <= 3000)
		{
			pauseDuration -= deltaTime;
			if (pauseDuration <= 0)
			{
				bPaused = false;
				pauseDuration = 4000;
			}
		}
	}
}

void Scene::render()
{
	RENDER_SHADERS;
	
	backBlack->render();
	backgSprite->render();
	ShaderCtrl::instance().setTranslateModelview();
	map->render();
	if (player->bePainted()) player->render();
	renderEnemies();

	HUD::instance().render();

	renderItems();
}

void Scene::flipGodMode() {
	if (!bPaused)
		player->flipGodMode();
}

void Scene::initMap()
{
	map = TileMap::createTileMap("levels/tilemap0" + std::to_string(stage) + ".txt",
								 glm::vec2(SCREEN_X, SCREEN_Y), TEX_PROGRAM);
}

void Scene::initLvl()
{
	lvl = Level::createLevel("levels/level0" + std::to_string(stage) + ".txt");
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

	for (Enemy* enemy : *enemies)
	{
		if (player->getHealth() > 0)
		{
			enemy->setPlayerTopLeft(playerTopLeft);
			enemy->setPlayerBotRight(playerBotRight);

			if (!player->hasClock()) enemy->update(deltaTime);

			if (!player->isHurt() && !player->isGodMode() && enemy->collision())
				player->hit();
		}
	}
}

void Scene::renderEnemies()
{
	for (Enemy* enemy : *enemies)
		if (enemy->bePainted()) enemy->render();
}

void Scene::unpaintEnemies()
{
	for (Enemy* enemy : *enemies)
		enemy->unpaint();
}

void Scene::initItems()
{
	items = lvl->getItems();
	for (Item* item : *items) {
		item->init();
	}
}

void Scene::updateItems(int deltaTime)
{
	glm::ivec2 playerTopLeft = player->getTopLeft();
	glm::ivec2 playerBotRight = player->getBotRight();

	for (Item* item : *items) {
		if (player->getHealth() > 0 && !item->isTaken())
		{
			item->setPlayerTopLeft(playerTopLeft);
			item->setPlayerBotRight(playerBotRight);
			if (item->getType() == 'K' && map->getNumTilesPisables() == 0)
				item->changeBPaint(true);

			item->update(deltaTime);

			if (item->getBPaint() && item->collision())
				player->takeItem(item->getType());
		}
	}
}

void Scene::renderItems()
{
	for (Item* item : *items) {
		item->render();
	}
}

void Scene::unpaintItems()
{
	for (Item* item : *items)
		item->changeBPaint(false);
}

void Scene::initHUD()
{
	HUD::instance().init();
	HUD::instance().update(player->getHealth(), player->getPuntuacion(), timer, stage);
}

void Scene::updateTimer(int deltaTime)
{
	timerCooldown -= deltaTime;
	if (timerCooldown <= 0) {
		timer -= 1;
		timerCooldown = 1000;
	}

	if (timer == 0)
	{
		if (player->getHealth() > 0)
			player->hit();

		if (player->getHealth() > 0)
			timer = 60;
	}
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

