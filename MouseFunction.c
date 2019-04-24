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
GLfloat x1,x2,yy1,yy2;

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3.0);
	glColor3f(1.0,0.0,0.0);

	glBegin(GL_POLYGON);
		glVertex2f(x1,yy1);
		glVertex2f(x1,yy2);
		glVertex2f(x2,yy2);
		glVertex2f(x2,yy1);
	glEnd();

	glFlush();
	return;
}

void MyMouse(GLint button, GLint state, GLint x, GLint y)
{
	static int first=1;

	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (first)
		{
			x1=(x-250.0)/250.0; 
			yy1=-(y-250)/250.0;;
		}
		else
		{
			x2=(x-250.0)/250.0;
			yy2=-(y-250)/250.0;
			glutPostRedisplay();
		}

		first = !first;
	}

	return;
}

void MyIdle()
{

	theta += 0.01;
	if (theta > 20111*M_PI) theta -= 2000*M_PI;
	glutPostRedisplay();

	return;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("mouse");
	glutDisplayFunc(display);
	glutMouseFunc(MyMouse);
	glutIdleFunc(MyIdle);


	glutMainLoop();
}