#include "StateCtrl.h"

void StateCtrl::changeTo(State* st)
{
	st->init();
	Game::instance().setState(st);
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



