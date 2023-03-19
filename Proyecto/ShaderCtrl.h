#ifndef _SHADERCTRL_INCLUDE
#define _SHADERCTRL_INCLUDE

#include "Definitions.h"


#include <glm/glm.hpp>

#include "ShaderProgram.h"


class ShaderCtrl
{

public:
	static ShaderCtrl &instance()
	{
		static ShaderCtrl SC;
		return SC;
	}

	void init();
	void render();

	ShaderProgram &getTexProgram();

private:
	ShaderProgram texProgram;
	glm::mat4 projection, modelview;

};
#endif //_SHADERCTRL_INCLUDE

