#include "Meadow.h"

Meadow::Meadow() : startX(-100), startZ(-100), endx(100), endz(100),
color{ 0.1f, 0.9f, 0.1f, 1.0f }{};

void Meadow::draw()
{
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3d(0, 0.5, 0);
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f },
		shininess = 128.0f;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

	/*
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	glVertex3d(startX * 1, 0, startZ * 32);
	glVertex3d(startX * 1, 0, endz * 32);
	glVertex3d((endx + 1) * 1, 0, (endz + 1) * 32);
	glVertex3d(endx * 1, 0, startZ * 32);*/
	
	for (int x = startX; x < endx; x++) {
		for (int z = startZ; z < endz; z++) {
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
			glVertex3d(x*1, 0, z * 32);
			glVertex3d((x + 1)*1, 0, z *32);
			glVertex3d((x + 1) * 1, 0, (z + 1) * 32);
			glVertex3d(x * 1, 0, (z + 1) * 32);
		}
	}

	glEnd();
	glPopMatrix();
}