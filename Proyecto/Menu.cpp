#include "Menu.h"

#include "MenuKeyboard.h"


Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::init()
{
	keyboardCtrl = &MenuKeyboard::instance();
}


void Menu::update(int deltaTime)
{

}

void Menu::render()
{
	RENDER_SHADERS;
}

