#ifndef _STATE_INCLUDE
#define _STATE_INCLUDE


#include "KeyboardCtrl.h"


class State
{

public:

	virtual void init() = 0;					// = 0 so that the class
	virtual void update(int deltaTime) = 0;		// is pure virtual
	virtual void render() = 0;					// (abstract)

	KeyboardCtrl *getKeyboardCtrl();

protected:
	KeyboardCtrl *keyboardCtrl;

};


#endif // _STATE_INCLUDE