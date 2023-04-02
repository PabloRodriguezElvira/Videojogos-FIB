#include <GL/glew.h>
#include <GL/glut.h>
#include "InfoKeyboard.h"
#include "Game.h"


void InfoKeyboard::keyPressed(int key)
{
	//If esc is pressed, return to Menu.
	if (key == 27) {
		StateCtrl::instance().changeToDialog(&Info::instance());
	}
}

void InfoKeyboard::keyReleased(int key)
{

}

void InfoKeyboard::specialKeyPressed(int key)
{

}

void InfoKeyboard::specialKeyReleased(int key)
{

}
