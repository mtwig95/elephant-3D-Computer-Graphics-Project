#pragma once
#include <math.h>
#include <GL/freeglut.h>

class Tree {
public:
	GLfloat position[4] = { -1.0f, 2.5f, 0.0f , 1.0f };
	GLfloat target[3] = { 0.1f, 0.0f, 0.0f };
	Tree();
	void draw();
	~Tree() = default;
private:
	void normalize(const GLfloat* vec, GLfloat* output);
	void cross(const GLfloat* vec1, const GLfloat* vec2, GLfloat* output);
	void lookAt(GLfloat* eye, GLfloat* center, GLfloat* up);
};
