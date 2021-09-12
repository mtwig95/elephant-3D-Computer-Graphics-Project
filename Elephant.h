#pragma once
#include <GL\freeglut.h>
#include <functional>




/*
The Dog object, renders the dog and exposes the dog controls to the ui.
*/
class Elephant
{
public:
	Elephant();
	GLfloat local[16];	//local coordinate system transformation matrix
	GLfloat headHorizontalAngle;
	GLfloat headVerticalAngle;
	GLfloat tailHorizontalAngle;
	GLfloat tailVerticalAngle;
	std::function<void()> nextMove;
	void moveHeadHorizontal(bool dir);
	void moveHeadVertical(bool dir);
	void moveTailHorizontal(bool dir);
	void moveTailVertical(bool dir);
	bool isMoving;

	void init();
	void draw();
	~Elephant() = default;
private:
	//update constant animation for tail wiggle and legs movement
	void updateConstantMovement();
	GLfloat legsAngle;
	bool legsMovementDirectionForward;
};
	
