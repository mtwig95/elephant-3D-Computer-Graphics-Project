#include "tree.h"

Tree::Tree() :position{ -1.0f, 2.5f, 0.0f , 1.0f },
target{ 0.1f, 0.0f, 0.0f }{};

/*void Tree::draw() {
		GLfloat ambient[] = { 0.5f, 0.5f, 0.5f },
			diffuse[] = { 0.9f, 0.9f, 0.9f },
			specular[] = { 1.0f, 1.0f, 1.0f },
			shininess = 128.0f;

		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

		glBegin(GL_QUADS);

		GLfloat step = 0.1f;
		for (GLfloat x = 0; x < 1.5; x += step) {
			for (GLfloat y = 0; y < 2.5; y += step) {
				glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, color);
				glVertex3d(x, y, 0);
				glVertex3d(x + step, y, 0);
				glVertex3d(x + step, y + step, 0);
				glVertex3d(x, y + step, 0);
			}
		}
		glEnd();
}*/

void Tree::draw() 
{
	

	glPushMatrix();
	GLfloat up[3] = { 0, 1, 0 };
	lookAt(position, target, up);

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.2, 0.8, 0.2);
	glutSolidSphere(1, 10, 10);
	glPushMatrix();
	glTranslatef(0, 0, 0.1f);
	glColor3f(0.6, 0.4, 0.2);
	glutSolidCylinder(0.2, 3, 10, 10);
	glPopMatrix();

	glPopMatrix();
	glDisable(GL_COLOR_MATERIAL);
}


void Tree::normalize(const GLfloat* vec, GLfloat* output)
{
	GLfloat length = sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	output[0] /= length;
	output[1] /= length;
	output[2] /= length;
}

void Tree::cross(const GLfloat* vec1, const GLfloat* vec2, GLfloat* output) {
	output[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	output[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	output[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

void Tree::lookAt(GLfloat* eye, GLfloat* center, GLfloat* up)
{
	GLfloat f[3] = { center[0] - eye[0],
		center[1] - eye[1],
		center[2] - eye[2] };

	normalize(f, f);
	GLfloat u[3];
	normalize(up, u);
	GLfloat s[3];
	cross(f, u, s);
	normalize(s, s);
	cross(s, f, u);
	normalize(u, u);

	GLfloat rotationMatrix[16];
	rotationMatrix[0] = s[0];
	rotationMatrix[1] = s[1];
	rotationMatrix[2] = s[2];
	rotationMatrix[3] = 0;

	rotationMatrix[4] = u[0];
	rotationMatrix[5] = u[1];
	rotationMatrix[6] = u[2];
	rotationMatrix[7] = 0;

	rotationMatrix[8] = -f[0];
	rotationMatrix[9] = -f[1];
	rotationMatrix[10] = -f[2];
	rotationMatrix[11] = 0;

	rotationMatrix[12] = 0;
	rotationMatrix[13] = 0;
	rotationMatrix[14] = 0;
	rotationMatrix[15] = 1;

	glMultMatrixf(rotationMatrix);
}