#include "MenuKeyboard.h"

#include "Game.h"


void MenuKeyboard::keyPressed(int key)
{
	if (key == 27) // Escape code
		Game::instance().setBplay(false);
	else if (key == GLUT_KEY_DOWN) {
		Menu::instance().changeMode();
	}
}

void MenuKeyboard::keyReleased(int key)
{

}

void MenuKeyboard::specialKeyPressed(int key)
{

}

void MenuKeyboard::specialKeyReleased(int key)
{

}