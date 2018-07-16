#pragma once
#include "auxiliary.h"
#include "Scene.h"
#include "Object.h"
#include "light.h"
#include "Camera.h"

/*We should focus on material in render field.And the material need to know everthing in the world.
So we put all in the Material file(Such as Lights,Cameras,Objects).*/
static GLint *open_tex = new GLint[3]{ 0,1,2 };
enum class MATERIAL_TYPE {
	PHONG
};
Lights lights;
list<Camera *>cameras;
Camera *current_cam;
list<Object *>objs;

class Material {
protected:
	list<Object*>objs;
	GLuint time_id;

	GLuint tex_id;
	GLuint UV_id;

	GLuint MVP_id;
	GLuint M_id;
	GLuint V_id;

	GLuint cam_worldid;
	GLuint li_worldid;
	GLuint li_colorid;

	GLuint program;
};

class PhongMat:public Material {
public:

	GLuint Normal_id;

	GLuint K_id;
	GLuint gloss_id;

	float K;
	float gloss;

	
	virtual void draw() {
		glUseProgram(program);
		mat4 model_mat;
		mat4 MVP;

		time_id		      = glGetUniformLocation(program, "time");
		K_id	          = glGetUniformLocation(program, "K");
		gloss_id	      = glGetUniformLocation(program, "gloss");

		V_id		      = glGetUniformLocation(program, "V");
		li_worldid		  = glGetUniformLocation(program, "li_world");
		li_colorid        = glGetUniformLocation(program, "li_color");

		GLuint cam_id	  = glGetUniformLocation(program, "cam_world");
		GLuint tex_id	  = glGetUniformLocation(program, "tex");

		glUniform1f(time_id, getTime());
		glUniform1f(K_id, K);
		glUniform1f(gloss_id, gloss);

		glUniformMatrix4fv(V_id, 1, GL_FALSE, &current_cam->V[0][0]);
		
		glUniform3fv(li_worldid,lights.posis.size(),&lights.posis[0][0])
		glUniform3fv(li_colorid, lights.colors.size(), &lights.colors[0][0]);
		glUniform3f(cam_id, current_cam->posi.x, current_cam->posi.y, current_cam->posi.z);
		glActiveTexture(GL_TEXTURE0);
		glActiveTexture(GL_TEXTURE1);
		glActiveTexture(GL_TEXTURE2);

		glUniform1iv(tex_id, 3, open_tex);


		for (const auto&obj : objs) {
			model_mat = obj->model_mat;
			MVP = current_cam->P * current_cam->V * obj->model_mat;
			GLuint MVPid = glGetUniformLocation(program, "MVP");
			GLuint ModelMatid = glGetUniformLocation(program, "M");
			glUniformMatrix4fv(MVPid, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatid, 1, GL_FALSE, &model_mat[0][0]);
		}


	}
};