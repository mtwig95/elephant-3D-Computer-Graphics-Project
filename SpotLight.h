#pragma once
#include <math.h>
#include <GL/freeglut.h>

/*
Spotlight object handling position, target and other lighting properties.
*/
class SpotLight {
public:
	GLfloat position[4] = { -1.0f, 2.5f, 0.0f , 1.0f };
	GLfloat target[3] = { 0.1f, 0.0f, 0.0f };
	GLfloat color[3] = { 1.0f, 1.0f, 1.0f };
	GLfloat cutoff = 30.0f;
	GLfloat exponent = 0.0f;
	int isOn = 1; 
	SpotLight();
	void addlight();
	void draw(bool without_move=true);
	void disable();
	void enable();
	void movePosition(bool dir, int axis);
	void moveTarget(bool dir, int axis);
	void changeCutoff(bool increase);
	void changeExponent(bool increase);
	~SpotLight() = default;
private:
	void normalize(const GLfloat* vec, GLfloat* output);
	void cross(const GLfloat* vec1, const GLfloat* vec2, GLfloat* output);
	void lookAt(GLfloat* eye, GLfloat* center, GLfloat* up);
};