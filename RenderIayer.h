#pragma once
#include"auxiliary.h"

class RenderLayer{
	virtual void setShaderProgram();
	virtual void updateGlobalEnvironmentInfo();
	virtual void bindPerVertexParameters();
	virtual void draw();
};

class glRender :public RenderLayer {
	struct globalEnvironmentINF {
		GLuint numLights;
		struct light {
			vec3 pos;
			vec3 color;
		};
		vec3 campos;
	};
	struct instancedObj {
		GLuint vao;

	};
	void setShaderProgram()override;
	void updateGlobalEnvironmentInfo()override;
	void bindPerVertexParameters()override;
	void draw()override;

protected:
	GLuint programid;
	GLuint vao;
	GLuint 
};

