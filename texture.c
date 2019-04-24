#include <GL/gl.h>
#include <GL/glext.h>
#include <H:/glut.h>
#include <math.h>
#include <stdio.h>


/*
This program illustrates texture mapping onto polygons.
There are two polygons separated along the z-axis.
There is a different texture for each polygon.
The texture in the array image is read in from a file 'texture.bin'
The texture in the array image2 is created by to for loops.
*/

	GLubyte image[64][64][3];
	GLubyte image2[64][64][3];

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(1.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

	glBegin(GL_POLYGON);
		glColor3f(1.0,0.0,0.0);
		glTexCoord2f(1.0,1.0);
		glVertex3f(0.5,0.5,0.0);
		glTexCoord2f(0.0,1.0);
		glVertex3f(-0.5,0.5,0.0);
		glTexCoord2f(0.0,0.0);
		glVertex3f(-0.5,-0.5,0.0);
		glTexCoord2f(1.0,0.0);
		glVertex3f(0.5,-0.5,0.0);
	glEnd();
		
	
	glFlush();
	return;
}


void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
	glFrustum(-1.0,1.0,-1.0,1.0,1.0,3.0);
	glViewport(0,0,w,h);
	return;
}




int main(int argc, char **argv)
{

	int i,j;
	FILE *fp;
	char buffer[4096],*pb;

	fp = fopen("texture.bin","r");
	fread(buffer, 4096,1,fp);

	pb = buffer;

	for(i=0; i<64; i++)
	   for(j=0; j<64; j++)
		{		
		image[i][j][0]=(GLubyte)*pb;
		image[i][j][1]=(GLubyte)*pb;
		image[i][j][2]=(GLubyte)*pb;
		pb++;
		}
	

	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);

	glEnable(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glutMainLoop();
}