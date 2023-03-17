#ifndef _SHADERCTRL_INCLUDE
#define _SHADERCTRL_INCLUDE

#define RENDER_SHADERS ShaderCtrl::instance().render()
#define TEX_PROGRAM ShaderCtrl::instance().getTexProgram()


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

