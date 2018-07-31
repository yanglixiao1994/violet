//#include <stdio.h>
//#include <stdlib.h>
//#include <assert.h>
//#include <random>
//#include <ctime>
//#include <vector>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//using namespace glm;
//#include <common/shader.hpp>
//#include <common/objloader.hpp>
//#include <common/controls.hpp>
//#include <common/texture.hpp>
//#define USE_ASSIMP
//#ifdef NDEBUG
//#define Assert(expr) expr
//#else
//#define Assert(expr) assert(expr)
//#endif
//std::clock_t c_start;
//GLFWwindow * window;
//int width, height;
//vec3 lightpos;
//vec3 lightcolor;
//float K;
//float gloss;
//GLuint texture;
//extern vec3 position;
//struct object {
//	GLsizei count;
//	GLuint vao;
//	GLuint program;
//	mat4 modelmat;
//	bool indices;
//	object(GLuint vao, GLuint program) :vao(vao), program(program), modelmat{ mat4{1.f} } {};
//	object():modelmat{ mat4{ 1.f } } {};
//	void rot(vec3 axis,float degree) {
//		modelmat = rotate(modelmat,degree/180.0f, axis);
//	}
//	void move(vec3 offset) {
//		modelmat = translate(modelmat, offset);
//	}
//	void scale_(vec3 factor) {
//		modelmat = scale(modelmat, factor);
//	}
//
//};
//GLuint createTriangle(int i)
//{
//	GLuint VAOID;
//	glGenVertexArrays(1, &VAOID);
//	glBindVertexArray(VAOID);
//	float offset = (float)i / 10.f;
//	GLfloat trangle_vertices[] = {
//		offset,.5f,0.f,
//		.5f,-.5f,0.f,
//		-.5f,-.5f,0.f,
//	};
//	GLuint VBOID;
//	glGenBuffers(1, &VBOID);
//	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(trangle_vertices), trangle_vertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(
//		0,
//		3,
//		GL_FLOAT,
//		GL_FALSE,
//		0,
//		(void*)0
//	);
//	return VAOID;
//}
//GLuint createBox(float length,float width,float height) {
//	GLfloat vertices[] = {
//		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
//		-1.0f,-1.0f, 1.0f,
//		-1.0f, 1.0f, 1.0f, // triangle 1 : end
//		1.0f, 1.0f,-1.0f, // triangle 2 : begin
//		-1.0f,-1.0f,-1.0f,
//		-1.0f, 1.0f,-1.0f, // triangle 2 : end
//		1.0f,-1.0f, 1.0f,
//		-1.0f,-1.0f,-1.0f,
//		1.0f,-1.0f,-1.0f,
//		1.0f, 1.0f,-1.0f,
//		1.0f,-1.0f,-1.0f,
//		-1.0f,-1.0f,-1.0f,
//		-1.0f,-1.0f,-1.0f,
//		-1.0f, 1.0f, 1.0f,
//		-1.0f, 1.0f,-1.0f,
//		1.0f,-1.0f, 1.0f,
//		-1.0f,-1.0f, 1.0f,
//		-1.0f,-1.0f,-1.0f,
//		-1.0f, 1.0f, 1.0f,
//		-1.0f,-1.0f, 1.0f,
//		1.0f,-1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,
//		1.0f,-1.0f,-1.0f,
//		1.0f, 1.0f,-1.0f,
//		1.0f,-1.0f,-1.0f,
//		1.0f, 1.0f, 1.0f,
//		1.0f,-1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f,-1.0f,
//		-1.0f, 1.0f,-1.0f,
//		1.0f, 1.0f, 1.0f,
//		-1.0f, 1.0f,-1.0f,
//		-1.0f, 1.0f, 1.0f,
//		1.0f, 1.0f, 1.0f,
//		-1.0f, 1.0f, 1.0f,
//		1.0f,-1.0f, 1.0f
//	};
//	GLuint verticesid;
//	GLuint colorsid;
//	GLuint vao;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//	glGenBuffers(1, &verticesid);
//	glBindBuffer(GL_ARRAY_BUFFER, verticesid);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(
//		0,
//		3,
//		GL_FLOAT,
//		GL_FALSE,
//		0,
//		nullptr
//	);
//	GLfloat colors[] = {
//		0.583f,  0.771f,  0.014f,
//		0.609f,  0.115f,  0.436f,
//		0.327f,  0.483f,  0.844f,
//		0.822f,  0.569f,  0.201f,
//		0.435f,  0.602f,  0.223f,
//		0.310f,  0.747f,  0.185f,
//		0.597f,  0.770f,  0.761f,
//		0.559f,  0.436f,  0.730f,
//		0.359f,  0.583f,  0.152f,
//		0.483f,  0.596f,  0.789f,
//		0.559f,  0.861f,  0.639f,
//		0.195f,  0.548f,  0.859f,
//		0.014f,  0.184f,  0.576f,
//		0.771f,  0.328f,  0.970f,
//		0.406f,  0.615f,  0.116f,
//		0.676f,  0.977f,  0.133f,
//		0.971f,  0.572f,  0.833f,
//		0.140f,  0.616f,  0.489f,
//		0.997f,  0.513f,  0.064f,
//		0.945f,  0.719f,  0.592f,
//		0.543f,  0.021f,  0.978f,
//		0.279f,  0.317f,  0.505f,
//		0.167f,  0.620f,  0.077f,
//		0.347f,  0.857f,  0.137f,
//		0.055f,  0.953f,  0.042f,
//		0.714f,  0.505f,  0.345f,
//		0.783f,  0.290f,  0.734f,
//		0.722f,  0.645f,  0.174f,
//		0.302f,  0.455f,  0.848f,
//		0.225f,  0.587f,  0.040f,
//		0.517f,  0.713f,  0.338f,
//		0.053f,  0.959f,  0.120f,
//		0.393f,  0.621f,  0.362f,
//		0.673f,  0.211f,  0.457f,
//		0.820f,  0.883f,  0.371f,
//		0.982f,  0.099f,  0.879f
//	};
//	glGenBuffers(1, &colorsid);
//	glBindBuffer(GL_ARRAY_BUFFER, colorsid);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(
//		1,
//		3,
//		GL_FLOAT,
//		GL_FALSE,
//		0,
//		nullptr
//	);
//	return vao;
//}
//GLuint createFloor(int length, int width,float metric) {
//	GLfloat *floor = new GLfloat[length * width];
//	return 0;
//}
//void   createObj(const char*file,object*obj) {
//	std::vector<unsigned short>indices;
//	std::vector<vec3>vertices;
//	std::vector<vec2>uvs;
//	std::vector<vec3>normals;
//	loadAssImp(file,indices, vertices, uvs, normals);
//	obj->count = indices.size();
//	GLuint vao;
//	glGenVertexArrays(1, &vao);
//	glBindVertexArray(vao);
//
//	GLuint vbo_i;
//	glGenBuffers(1, &vbo_i);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(short), &indices[0], GL_STATIC_DRAW);
//	
//	GLuint vbo_v;
//	glGenBuffers(1, &vbo_v);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), &vertices[0], GL_STATIC_DRAW);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(
//		0, 
//		3, 
//		GL_FLOAT, 
//		GL_FALSE, 
//		0, 
//		nullptr
//	);
//	
//	GLuint vbo_uv;
//	glGenBuffers(1, &vbo_uv);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo_uv);
//	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(vec2), &uvs[0], GL_STATIC_DRAW);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(
//		1, 
//		2, 
//		GL_FLOAT, 
//		GL_FALSE, 
//		0, 
//		nullptr
//	);
//	
//	GLuint vbo_n;
//	glGenBuffers(1, &vbo_n);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo_n);
//	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(vec3), &normals[0], GL_STATIC_DRAW);
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(
//		2, 
//		3, 
//		GL_FLOAT, 
//		GL_FALSE, 
//		0, 
//		nullptr
//	);
//	obj->vao = vao;
//	obj->indices = true;
//}
//mat4   createMVP(float fov,float aspect,float near,float far,const vec3& campos,const vec3&at,const mat4&model) {
//	mat4 v = lookAt(campos,at,vec3(0,1,0));
//	mat4 p = perspective(fov, aspect, near, far);
//	return p * v * model;
//}
//GLuint createShaderProgram(const char*vertex,const char*segment) {
//	GLuint programid = LoadShaders(vertex,segment);
//	return programid;
//}
//void   init(int width, int height) {
//	Assert(glfwInit());
//	glfwWindowHint(GLFW_SAMPLES, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	window = glfwCreateWindow(width, height, "Soft body FEM", NULL, NULL);
//
//	Assert(window);
//	glfwMakeContextCurrent(window);
//	glewExperimental = GL_TRUE;
//
//	Assert(glewInit() == GLEW_OK);
//	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
//	glClearColor(0.f, 0.f, .4f, 0.f);
//
//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LESS);
//	glEnable(GL_CULL_FACE);
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
//
//	texture = loadDDS("uvmap.DDS");
//}
//void   draw(object* objs, int num) {
//	do {
//		glClear(GL_COLOR_BUFFER_BIT);
//		for (int i = 0; i < num; i++) {
//			glUseProgram(objs[i].program);
//			glBindVertexArray(objs[i].vao);
//			glActiveTexture(GL_TEXTURE0);
//			glBindTexture(GL_TEXTURE_2D, texture);
//			std::clock_t c_end = std::clock();
//			float time = (c_end - c_start) / CLOCKS_PER_SEC;
//			computeMatricesFromInputs();
//			mat4 proj = getProjectionMatrix();
//			mat4 view = getViewMatrix();
//			mat4 MVP = proj * view * objs[i].modelmat;
//		
//			GLuint timeid     = glGetUniformLocation(objs[i].program, "time");
//			GLuint Kid        = glGetUniformLocation(objs[i].program, "K");
//			GLuint glossid	  = glGetUniformLocation(objs[i].program, "gloss");
//			GLuint MVPid      = glGetUniformLocation(objs[i].program, "MVP");
//			GLuint ModelMatid = glGetUniformLocation(objs[i].program, "M");
//			GLuint ViewMatid  = glGetUniformLocation(objs[i].program, "V");
//			GLuint lightposid = glGetUniformLocation(objs[i].program, "li_world");
//			GLuint colorid    = glGetUniformLocation(objs[i].program, "li_color");
//			GLuint camid	  = glGetUniformLocation(objs[i].program, "cam_world");
//			GLuint tex1		  = glGetUniformLocation(objs[i].program, "tex1");
//
//			glUniform1f(timeid, time);
//			glUniform1f(Kid, K);
//			glUniform1f(glossid, gloss);
//			glUniformMatrix4fv(MVPid, 1, GL_FALSE, &MVP[0][0]);
//			glUniformMatrix4fv(ModelMatid, 1, GL_FALSE, &objs[i].modelmat[0][0]);
//			glUniformMatrix4fv(ViewMatid, 1, GL_FALSE, &view[0][0]);
//			glUniform3f(lightposid, lightpos.x, lightpos.y, lightpos.z);
//			glUniform3f(colorid, lightcolor.x, lightcolor.y, lightcolor.z);
//			glUniform3f(camid, position.x, position.y, position.z);
//			glUniform1i(tex1, 0);
//
//			if (objs[i].indices) {
//				glDrawElements(GL_TRIANGLE_STRIP, objs[i].count, GL_UNSIGNED_SHORT, nullptr);
//			}
//			else
//				glDrawArrays(GL_TRIANGLES, 0, objs[i].count);
//		}
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
//		glfwWindowShouldClose(window) == 0);
//}
//int main()
//{
//	width     = 1024;
//	height    = 768;
//	lightpos  = vec3(20, 20, 20);
//	lightcolor= vec3(.3f, .6f, .2f);
//	K		  = .4f;
//	gloss	  = 2;
//	init(width,height);
//	object obj;
//	createObj("plant.obj", &obj);
//	obj.program = LoadShaders("wave.vertex", "wave.fragment");
//	c_start = std::clock();
//	draw(&obj,1);
//	glfwTerminate();
//	return 0;
//}
