#ifndef _MENU_INCLUDE
#define _MENU_INCLUDE

#include "Definitions.h"


#include "State.h"


class Menu : public State
{

public:
	static Menu &getInstance()
	{
		static Menu M;
		return M;
	};

	
	void init();
	void update(int deltaTime);
	void render();


private:
	Menu();
	~Menu();

};


#endif // _MENU_INCLUDE