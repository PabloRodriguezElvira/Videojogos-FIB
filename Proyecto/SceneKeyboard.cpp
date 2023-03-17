#include "SceneKeyboard.h"
#include "Game.h"


void SceneKeyboard::keyPressed(int key)
{
	if (key == 27) // Escape code
		Game::instance().setBplay(false);
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