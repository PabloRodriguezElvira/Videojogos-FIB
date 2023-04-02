#ifndef _STATE_INCLUDE
#define _STATE_INCLUDE


#include "KeyboardCtrl.h"


class State
{

public:

	virtual void init() = 0;					// = 0 so that the class
	virtual void update(int deltaTime) = 0;		// is pure virtual
	virtual void render() = 0;					// (abstract)
	virtual void pause() = 0;
	virtual void unpause() = 0;

	KeyboardCtrl *getKeyboardCtrl();

protected:
	KeyboardCtrl *keyboardCtrl;
	bool bPaused;

};


#endif // _STATE_INCLUDE