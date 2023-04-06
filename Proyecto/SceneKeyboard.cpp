#include "SceneKeyboard.h"
#include "Game.h"


void SceneKeyboard::keyPressed(int key)
{
	//Escape key:
	if (key == 27 && !Scene::instance().isPaused()) {
		StateCtrl::instance().pause(&Scene::instance());
		StateCtrl::instance().changeToDialog(&Scene::instance());
	}
	if (key == 'g' || key == 'G')
		Scene::instance().flipGodMode();
	if (key == 'k' || key == 'K')
		Scene::instance().giveKey();

	if (key == '1' || key == '2' || key == '3')
		StateCtrl::instance().changeStage(key-48, 0, 3);
}

void SceneKeyboard::keyReleased(int key)
{

}

void SceneKeyboard::specialKeyPressed(int key)
{
}

void SceneKeyboard::specialKeyReleased(int key)
{

}