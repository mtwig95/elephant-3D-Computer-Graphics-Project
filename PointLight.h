#pragma once
#include <GL\freeglut.h>

/*
PointLight is light source with uniform light distribution.
*/
class PointLight
{
public:
	GLfloat color[4];
	GLfloat position[8];

	PointLight();
	void addLight();
	void draw();
	void enable();
	~PointLight() = default;
};

