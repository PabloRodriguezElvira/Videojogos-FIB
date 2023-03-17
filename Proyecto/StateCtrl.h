#ifndef _STATECTRL_INCLUDE
#define _STATECTRL_INCLUDE


#include "State.h"


class StateCtrl
{

public:

	static StateCtrl &instance()
	{
		static StateCtrl SC;
		return SC;
	};

	

};


#endif // _STATECTRL_INCLUDE