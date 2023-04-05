#ifndef _STATECTRL_INCLUDE
#define _STATECTRL_INCLUDE


#include "State.h"
#include "Menu.h"
#include "Info.h"
#include "Game.h"
#include "ConfirmationDialog.h"


class StateCtrl
{

public:

	static StateCtrl &instance()
	{
		static StateCtrl SC;
		return SC;
	};

	void changeTo(State* st);
	void changeStage(int stage);
	void changeToDialog(State* st);
	void pause(State* st);
	void unpause(State* st);
};


#endif // _STATECTRL_INCLUDE