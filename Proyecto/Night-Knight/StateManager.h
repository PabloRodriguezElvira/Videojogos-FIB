#ifndef _STATEMANAGER_INCLUDE
#define _STATEMANAGER_INCLUDE


class StateManager
{
public:
	virtual void init();
	virtual void update(int deltaTime);
	virtual void render();
};


#endif

