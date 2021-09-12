#pragma once
#include <GL\freeglut.h>

/*
The meadow
*/
class Meadow
{
public:
	Meadow();
	void draw();
	~Meadow() = default;
private:
	int startX, startZ, endx, endz;
	GLfloat color[4];
};

