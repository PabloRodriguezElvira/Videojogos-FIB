#include <GL/glew.h>
#include <GL/glut.h>
#include "DialogKeyboard.h"
#include "Game.h"

void DialogKeyboard::keyPressed(int key)
{
	State* st = ConfirmationDialog::instance().getState();
	int mode = ConfirmationDialog::instance().getMode();

	//Escape o enter al No.
	if (key == 27 || (key == 13 && mode == 1)) {
		StateCtrl::instance().unpause(st);
		Game::instance().setState(st);
	}
	//Enter al Yes.
	else if (key == 13 && mode == 0) {
		//Si estamos en Menu, salimos del juego.
		if (st == &Menu::instance()) {
			Game::instance().setBplay(false);
		}
		//Si no, volvemos al Menu.
		else {
			//Volvemos al track del menú principal si no estamos en OPCIONES.
			int modeMenu = st->getMode();
			if (modeMenu != 1) {
				SoundCtrl::instance().endMusic();
				SoundCtrl::instance().putTrack("sounds/Menu/House.mp3", 0.1f);
			}
			StateCtrl::instance().unpause(&Menu::instance());
		}
	}
}

void DialogKeyboard::keyReleased(int key)
{

}

void DialogKeyboard::specialKeyPressed(int key)
{
	if (key == GLUT_KEY_RIGHT) {
		ConfirmationDialog::instance().changeModeRight();
	}
	else if (key == GLUT_KEY_LEFT) {
		ConfirmationDialog::instance().changeModeLeft();
	}
}

void DialogKeyboard::specialKeyReleased(int key)
{

}
