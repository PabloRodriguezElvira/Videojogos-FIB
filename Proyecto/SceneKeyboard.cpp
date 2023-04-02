#include "SceneKeyboard.h"
#include "Game.h"


void SceneKeyboard::keyPressed(int key)
{
	//Escape key:
	if (key == 27) {
		StateCtrl::instance().pause(&Scene::instance());
		StateCtrl::instance().changeToDialog(&Scene::instance());
	}
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