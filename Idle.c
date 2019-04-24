#include <GL/gl.h>
#include <GL/glext.h>
#include <H:/glut.h>
#include <math.h>

/* 
This program illustrates the use of the Idle Callback,
in this case to carry out some animation.
It draws a rotating square.
*/

float theta = M_PI/4;

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,0.0,0.0);

	GLfloat x=cos(theta), y=sin(theta);

	glBegin(GL_POLYGON);
		glVertex2f(-x,-y);
		glVertex2f(-y,x);
		glVertex2f(x,y);
		glVertex2f(y,-x);
	glEnd();

	glFlush();
	return;
}

void MyIdle()
{

	theta += 0.001;
	if (theta > 2*M_PI) theta -= 2*M_PI;
	glutPostRedisplay();

	return;
}
	
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("rotating square");
	glutDisplayFunc(display);
	glutIdleFunc(MyIdle);


	glutMainLoop();
}