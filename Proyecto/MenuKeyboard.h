#ifndef _MENUKEYBOARD_INCLUDE
#define _MENUKEYBOARD_INCLUDE

#include "StateCtrl.h"
#include "SoundCtrl.h"
#include "KeyboardCtrl.h"

class MenuKeyboard : public KeyboardCtrl
{

public:
	static MenuKeyboard& instance()
	{
		static MenuKeyboard MK;
		return MK;
	};

	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);

	//Menu songs:
	string tracks[4] = { "/sounds/Menu/House.mp3", "/sounds/Menu/House.mp3", "/sound/Menu/EzloAppears.mp3", "/sound/Menu/House.mp3"};
};
#endif // _MENUKEYBOARD_INCLUDE