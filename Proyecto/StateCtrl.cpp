#include "StateCtrl.h"

void StateCtrl::changeTo(State* st)
{
	SoundCtrl::instance().endMusic();
	st->init();
	Game::instance().setState(st);
}

void StateCtrl::changeStage(int stage)
{
	SoundCtrl::instance().endMusic();
	Scene::instance().changeStage(stage);
	Scene::instance().init();
	Game::instance().setState(&Scene::instance());
}

void StateCtrl::pause(State* st)
{
	st->pause();
	Game::instance().setState(st);
}

void StateCtrl::unpause(State* st)
{
	st->unpause();
	Game::instance().setState(st);
}

void StateCtrl::changeToDialog(State* st)
{
	ConfirmationDialog::instance().init();
	ConfirmationDialog::instance().setState(st);
	Game::instance().setState(&ConfirmationDialog::instance());
}



