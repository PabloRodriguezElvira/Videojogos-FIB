#include <GL/glew.h>
#include <GL/glut.h>
#include "MenuKeyboard.h"
#include "Game.h"
#include "Info.h"
#include "StateCtrl.h"
#include "SoundCtrl.h"
#include <iostream>


void MenuKeyboard::keyPressed(int key)
{
	int mode = Menu::instance().getMode();

	//Escape code or Enter at exit:
	if ((key == 27) || (key == 13 && mode == 3)) {
		StateCtrl::instance().pause(&Menu::instance());
		StateCtrl::instance().changeToDialog(&Menu::instance());
	}
	//Enter:
	else if (key == 13) {
		if (mode == 0) //ESCENA
			StateCtrl::instance().changeTo(&Scene::instance());

		else
		{
			Info::instance().setMode(mode);
			StateCtrl::instance().changeTo(&Info::instance());
		}
	}

	if (key == '1' || key == '2' || key == '3')
		StateCtrl::instance().changeStage(key - 48);
}

void MenuKeyboard::keyReleased(int key)
{

}

void MenuKeyboard::specialKeyPressed(int key)
{
	if (key == GLUT_KEY_UP) {
		Menu::instance().changeModeUp();
	}
	else if (key == GLUT_KEY_DOWN) {
		Menu::instance().changeModeDown();
	}
}

void MenuKeyboard::specialKeyReleased(int key)
{

}