#include <GL\freeglut.h>
#include <windows.h>
#include <iostream>
#include "Content.h"

using namespace std;

Content content;

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture


void keyboard(int key, int, int) {
	content.move(key);
	glutPostRedisplay();
}

void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //Escape key
		exit(0);
		break;
	case 'e':
		if (content.isElephantView == 0) {
			printf("~Elephant view: control with the arrow keys.\n");
			content.isElephantView = 1;
			content.movement = ELEPHANT_WALK;
		}
		else
		{
			printf("~Camera view: control with the arrow keys.\n");
			content.isElephantView = 0;
			}
		break;
	case 'w':
		printf("~Elephant movement: control with the arrow keys.\n");
		content.movement = ELEPHANT_WALK;
		content.camera_source_or_point = 0;
		break;
	case 't':
		printf("~Tail movement: control with the arrow keys.\n");
		content.movement = ELEPHANT_TAIL;
		content.camera_source_or_point = 0;
		break;
	case 'h':
		printf("~Head movement: control with the arrow keys.\n");
		content.movement = ELEPHANT_HEAD;
		content.camera_source_or_point = 0;
		break;
	case 'c':
		if (content.isElephantView == 0) {
			printf("~Camera control:\ns - control the source of the camera.\np - control the point.\nw- control the elephant movment.\n");
			content.movement = CAMERA_EXT;
		}
		else {
			printf("~Elephant control: control with the arrow keys.\n");
			content.movement = ELEPHANT_WALK;
		}
		break;
	case 'b':
		if (content.isElephantView == 0) {
			printf("~Spotlight control:\ns - control the source of the spotlight.\np - control the point.\nw- control the elephant movment.\n");
			content.movement = SPOTLIGHT;
		}
		else {
			printf("~Elephant control: control with the arrow keys.\n");
			content.movement = ELEPHANT_WALK;
		}
		break;
	case 's':
		if (content.movement == CAMERA_EXT)
		{
			printf("~Camera source:\nx/y/z - to control the axiz with up/down keys.\nr- reset camera.\n");
			content.camera_source_or_point = 1;
		}
		else if (content.movement == SPOTLIGHT)
		{
			printf("~Spotlight source:\nx/y/z - to control the axiz with up/down keys.\n");
			content.spotlight_source_or_point = 1;
		}
		break;
	case 'p':
		if (content.movement == CAMERA_EXT)
		{
			printf("~Camera target location:\nx/y/z - to control the axiz with up/down keys.\nr- reset camera.\n");
			content.camera_source_or_point = 2;
		}
		else if (content.movement == SPOTLIGHT)
		{
			printf("~Spotlight target location:\nx/y/z - to control the axiz with up/down keys\n");
			content.spotlight_source_or_point = 2;
		}
		break;
	case 'r':
		printf("~Reset display~\n");
		if (content.movement == CAMERA_EXT)
			content.camera.reset();
		break;
	case 'x':
		if (content.movement == CAMERA_EXT) 
		{
			if (content.camera_source_or_point == 1)
				content.camera_movement = SOURCE_X;
			else if(content.camera_source_or_point == 2)
				content.camera_movement = POINT_X;
		}
		else if (content.movement == SPOTLIGHT)
		{
			if (content.spotlight_source_or_point == 1)
				content.spotlight_movement = SOURCE_X_LIGHT;
			else if (content.spotlight_source_or_point == 2)
				content.spotlight_movement = POINT_X_LIGHT;
		}
		break;
	case 'y':
		if (content.movement == CAMERA_EXT) 
		{
			if (content.camera_source_or_point == 1)
				content.camera_movement = SOURCE_Y;
			else if (content.camera_source_or_point == 2)
				content.camera_movement = POINT_Y;
		}
		else if (content.movement == SPOTLIGHT)
		{
			if (content.spotlight_source_or_point == 1)
				content.spotlight_movement = SOURCE_Y_LIGHT;
			else if (content.spotlight_source_or_point == 2)
				content.spotlight_movement = POINT_Y_LIGHT;
		}
		break;
	case 'z':
		if (content.movement == CAMERA_EXT) {
			if (content.camera_source_or_point == 1)
				content.camera_movement = SOURCE_Z;
			else if (content.camera_source_or_point == 2)
				content.camera_movement = POINT_Z;
		}
		else if (content.movement == SPOTLIGHT)
		{
			if (content.spotlight_source_or_point == 1)
				content.spotlight_movement = SOURCE_Z_LIGHT;
			else if (content.spotlight_source_or_point == 2)
				content.spotlight_movement = POINT_Z_LIGHT;
		}
		break;
	case 'l': //for now just lighter
		printf("~Point light control:\n position - control with the arrow keys.\npower - \nambient - ");
		content.pointlight.color[0] += 0.05f;
		content.pointlight.color[1] += 0.05f;
		content.pointlight.color[2] += 0.05f;
		break;

	case 'k': //for now just darker
		printf("~Point light control:\n position - control with the arrow keys.\npower - \nambient - ");
		content.pointlight.color[0] -= 0.05f;
		content.pointlight.color[1] -= 0.05f;
		content.pointlight.color[2] -= 0.05f;
		break;
	case 'm': 
		printf("");
		for (int i = 0; i < 8; i++) {
			content.spotlights[i].changeCutoff(true);
		}
		content.moving_spotlight.changeCutoff(true);
		break;
	case 'n':
		printf("");
		for (int i = 0; i < 8; i++) {
			content.spotlights[i].changeCutoff(false);
		}		
		content.moving_spotlight.changeCutoff(false);
		break;
	case 'i':
		for (int i = 0; i < 8; i++) {
			content.spotlights[i].changeExponent(true);
		}
		content.moving_spotlight.changeExponent(true);
		break;
	case 'j':
		for (int i = 0; i < 8; i++) {
			content.spotlights[i].changeExponent(false);
		}
		content.moving_spotlight.changeExponent(false);
		break;
	case '=':
		if (content.globalAmbient <= 1.0f)
			content.globalAmbient += 0.01;
		break;
	case '-':
		if (content.globalAmbient >= 0.0f)
			content.globalAmbient -= 0.01;
		break;
	case 'f':
		content.isFollowElephant = !content.isFollowElephant;
		if(content.isFollowElephant)
			printf("~Camera follow elephant \n");
		else
			printf("~Camera stop following elephant \n");
		break;
	}
}

void location_of_tree(int& x_pos, int iteration) {
	if (iteration < 40) {
		x_pos = 10;
	}
	else if (iteration < 80) {
		x_pos = 15;
	}
	else if (iteration < 120) {
		x_pos = 20;
	}
	else if (iteration < 160) {
		x_pos = 25;
	}
	else if (iteration < 200) {
		x_pos = 30;
	}
	else if (iteration < 240) {
		x_pos = 35;
	}
	else if (iteration < 280) {
		x_pos = 40;
	}
	else if (iteration < 320) {
		x_pos = 45;
	}
	else if (iteration < 360) {
		x_pos = 50;
	}
	else if (iteration < 400) {
		x_pos = 55;
	}



}

void drawScene() {
	// trees from the right
	for (int i = 0; i < 400; i++) {
		int x_pos;
		location_of_tree(x_pos, i);

		glPushMatrix();
		glTranslatef(x_pos, 3, -80 + (i % 40) * 4);
		glRotatef(0, 1, 0, 0);
		glRotatef(0, 0, 1, 0);
		glRotatef(-200, 0, 0, 1);
		content.trees[i].draw();
		glPopMatrix();
	}

	// trees from the left
	for (int i = 400; i < 800; i++) {
		int x_pos;
		location_of_tree(x_pos, i-400);

		glPushMatrix();
		glTranslatef(-x_pos + 5, 3, -80 + (i % 40) * 4);
		glRotatef(0, 1, 0, 0);
		glRotatef(0, 0, 1, 0);
		glRotatef(-200, 0, 0, 1);
		content.trees[i].draw();
		glPopMatrix();
	}
	

	
	// trees in the middle
	for (int i = 800; i < 817; i++) {
		glPushMatrix();
		glTranslatef(0, 3, 12 + (i % 40) * 4);
		glRotatef(0, 1, 0, 0);
		glRotatef(0, 0, 1, 0);
		glRotatef(-200, 0, 0, 1);
		content.trees[i].draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(5, 3, 12 + (i % 40) * 4);
		glRotatef(0, 1, 0, 0);
		glRotatef(0, 0, 1, 0);
		glRotatef(-200, 0, 0, 1);
		content.trees[i+17].draw();
		glPopMatrix();
	}

	for (int i = 834; i < 849; i++) {
		int z = i - 834;
		glPushMatrix();
		glTranslatef(0, 3, -80 + (z % 40) * 4);
		glRotatef(0, 1, 0, 0);
		glRotatef(0, 0, 1, 0);
		glRotatef(-200, 0, 0, 1);
		content.trees[i].draw();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(5, 3, -80 + (z % 40) * 4);
		glRotatef(0, 1, 0, 0);
		glRotatef(0, 0, 1, 0);
		glRotatef(-200, 0, 0, 1);
		content.trees[i + 15].draw();
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(-3, 3, -5);
	glRotatef(0, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(-200, 0, 0, 1);
	content.spotlights[0].draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 3, 0);
	glRotatef(0, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(-200, 0, 0, 1);
	content.spotlights[1].draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 3, 5);
	glRotatef(0, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(-200, 0, 0, 1);
	content.spotlights[2].draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-3, 3, 10);
	glRotatef(0, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(-200, 0, 0, 1);
	content.spotlights[3].draw();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(6, 3, -5);
	glRotatef(0, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(-200, 0, 0, 1);
	content.spotlights[4].draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 3, 0);
	glRotatef(0, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(-200, 0, 0, 1);
	content.spotlights[5].draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 3, 5);
	glRotatef(0, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(-200, 0, 0, 1);
	content.spotlights[6].draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(6, 3, 10);
	glRotatef(0, 1, 0, 0);
	glRotatef(0, 0, 1, 0);
	glRotatef(-200, 0, 0, 1);
	content.spotlights[7].draw();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(content.pointlight.position[0], content.pointlight.position[1], content.pointlight.position[2]);
	content.pointlight.addLight();
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(content.moving_spotlight.position[0], content.moving_spotlight.position[1], content.moving_spotlight.position[2]);
	content.moving_spotlight.addlight();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(content.moving_spotlight.position[0], content.moving_spotlight.position[1], content.moving_spotlight.position[2]);
	content.moving_spotlight.draw(false);
	glPopMatrix();

	content.meadow.draw();

	glPushMatrix();
	glMultMatrixf(content.elephant.local);
	content.elephant.draw();
	glPopMatrix();

	glPushMatrix();
	content.building.draw(_textureId);
	glPopMatrix();
}

void display() {

	glViewport(0, 0, (GLsizei)1400, (GLsizei)700);
	glClearColor(0.01f, 0.6f, 0.9f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, 2.0, 1.0, 150.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	//update the elephant's transformation matrix
	if (content.elephant.nextMove) {
		content.elephant.isMoving = true;
		GLfloat viewModelMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
		glLoadMatrixf(content.elephant.local);
		content.elephant.nextMove();
		content.elephant.nextMove = nullptr;
		glGetFloatv(GL_MODELVIEW_MATRIX, content.elephant.local);
		glLoadMatrixf(viewModelMatrix);
	}

	//change viewing mode if in elephantgy view setup
	if (content.isElephantView) {
		GLfloat viewModelMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
		glLoadMatrixf(content.elephant.local);

		glRotatef(content.elephant.headVerticalAngle, 1, 0, 0);
		glRotatef(content.elephant.headHorizontalAngle, 0, 1, 0);
		glTranslated(0, 0.75, 0.9);

		GLfloat cameraPoseInelephantView[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, cameraPoseInelephantView);
		glLoadMatrixf(viewModelMatrix);

		GLfloat zAngle = atan2(-cameraPoseInelephantView[2], cameraPoseInelephantView[0]);
		GLfloat yAngle = atan2(-cameraPoseInelephantView[9], cameraPoseInelephantView[5]);

		gluLookAt(cameraPoseInelephantView[12], cameraPoseInelephantView[13], cameraPoseInelephantView[14],
			sin(zAngle) + cameraPoseInelephantView[12],
			-yAngle + cameraPoseInelephantView[13],
			cos(zAngle) + cameraPoseInelephantView[14],
			0, 1, 0);
	}
	else if (content.isFollowElephant)
	{
		GLfloat viewModelMatrix[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, viewModelMatrix);
		glLoadMatrixf(content.elephant.local);

		glRotatef(content.elephant.headVerticalAngle, 1, 0, 0);
		glRotatef(content.elephant.headHorizontalAngle, 0, 1, 0);
		glTranslated(0, 0.75, 0.9);

		GLfloat cameraPoseInelephantView[16];
		glGetFloatv(GL_MODELVIEW_MATRIX, cameraPoseInelephantView);
		glLoadMatrixf(viewModelMatrix);

		GLfloat zAngle = atan2(-cameraPoseInelephantView[2], cameraPoseInelephantView[0]);
		GLfloat yAngle = atan2(-cameraPoseInelephantView[9], cameraPoseInelephantView[5]);
		//view mode of camera view setup
		gluLookAt(content.camera.position[0], content.camera.position[1], content.camera.position[2],
			sin(zAngle) + cameraPoseInelephantView[12],
			-yAngle + cameraPoseInelephantView[13],
			cos(zAngle) + cameraPoseInelephantView[14], 0, 1, 0);
	}
	else
	{
		//view mode of camera view setup
		gluLookAt(content.camera.position[0], content.camera.position[1], content.camera.position[2],
			content.camera.point[0], content.camera.point[1], content.camera.point[2], 0, 1, 0);
	}
	GLfloat globalAmbientVec[4] = { content.globalAmbient, content.globalAmbient, content.globalAmbient, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbientVec);
	
	drawScene();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

GLfloat red = 1.0, green = 1.0, blue = 1.0; // Initial color values.
GLenum renderingMode = GL_SMOOTH; // Initial fill method.


void initRendering() {
	Image* image = loadBMP("brick2.bmp");
	_textureId = loadTexture(image);
	delete image;
}


void init(void)
{
	glClearColor(0.6, 0.6, 0.6, 1.0); // Set display-window color to gray.
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 300.0, 0.0, 300.0);
}

void mainMenu(GLint renderingOption)
{
	switch (renderingOption) {
	case 1: 
	{
		printf("Instructions:\n The control performed with the arrow keys, each key controls:\nw - Elephant movement.\nt - Tail movement.\nh - Head movement.");
		printf("\ne - Switching between seeing the elephant view or the camera view.\n");
		printf("c - Camera shifts.\nb - spotlight shifts.\n \n\nfor Camera and spotlight shifts:\ns - The source location (where to look at the specific point).\np - The target location (which point to look at).\nYou can now press x, y and z to move the corresponding axes(with the up and down arrows)\nr - Reset display, if we are in camera shifts(i.e.we pressed c sometime).");
		break;
	}
	case 2:
		exit(0);
			break;
	}
	glutPostRedisplay();
}

void adjustAmbientLight(GLint ambient)
{
	switch (ambient) {
	case 1:
		content.globalAmbient += 0.1;
		break;
	case 2:

		content.globalAmbient -= 0.1;
		break;
	}
}

void pointLightPower(GLint power)
{
	switch (power) {
	case 1:
		content.pointlight.color[0] += 0.05f;
		content.pointlight.color[1] += 0.05f;
		content.pointlight.color[2] += 0.05f;
		break;
	case 2:// position 
		content.pointlight.color[0] -= 0.05f;
		content.pointlight.color[1] -= 0.05f;
		content.pointlight.color[2] -= 0.05f;
		break;
	}

}

int main(int argc, char** argv) {
	GLint subMenu;
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE | GLUT_STENCIL);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(1200, 600);
	glutCreateWindow("opengl elephant scene");
	initRendering();

	glutDisplayFunc(display);

	glutSpecialFunc(keyboard);
	glutKeyboardFunc(handleKeypress);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for(int i=0; i<8; i++)
		content.spotlights[i].enable();
	content.moving_spotlight.enable();

	content.pointlight.enable();
	content.elephant.init();
	//menu
	
	subMenu = glutCreateMenu(adjustAmbientLight);
	glutAddMenuEntry("lighter", 1);
	glutAddMenuEntry("darker", 2);
	
	glutCreateMenu(mainMenu); // Create main pop-up menu.
	glutAddMenuEntry("Help", 1);
	glutAddMenuEntry("Quit", 2);
	glutAddSubMenu("Adjust ambient light", subMenu);
	
	/* Select menu option using right mouse button. */
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	subMenu = glutCreateMenu(pointLightPower);
	glutAddMenuEntry("lighter", 1);
	glutAddMenuEntry("darker", 2);

	glutMainLoop();

	return 0;
}