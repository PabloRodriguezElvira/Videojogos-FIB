#include <GL/glew.h>
#include <GL/glut.h>
#include "MenuKeyboard.h"
#include "Game.h"
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
		if (mode == 0) { //ESCENA
			SoundCtrl::instance().endMusic();
			StateCtrl::instance().changeTo(&Scene::instance());
		}
		else {
			if (mode == 2) { //Creditos (No paramos el sonido).		
				SoundCtrl::instance().endMusic();
			}
			Info::instance().setMode(mode);
			StateCtrl::instance().changeTo(&Info::instance());
		}
	}
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