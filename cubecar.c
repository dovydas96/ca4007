#include <GL/gl.h>
#include <GL/glext.h>
#include <H:/glut.h>
#include <math.h>
float i = 2;
float theta = M_PI/4;

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,0.0,4.0,0.0,0.0,0.0,0.0,1.0,0.0);


	GLfloat ambient[4] ={ 0.0215, 0.1745, 0.0215, 0.55 };
	GLfloat diffuse[4] ={0.07568, 0.61424, 0.07568, 0.55 };
	GLfloat specular[4] ={0.633, 0.727811, 0.633, 0.55 };
	GLfloat shine = 76.8;
          

	// GLfloat  ambient[4] = {0.33,0.22,0.03,1.0};
	// GLfloat diffuse[4] = {0.78,0.57,0.11,1.0};
	// GLfloat specular[4] = {0.99,0.91,0.81,1.0};
	// GLfloat shininess = 27.3;
	GLfloat normal[3] = {0.0,0.0,1.0};
	GLfloat position[4] = {1.0,1.0,1.0,1.0};

	position[1]=cos(theta); position[2]=sin(theta);

	glLightfv(GL_LIGHT0, GL_POSITION, position);

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32.0);

	glPushMatrix();
	glTranslatef(i,0.0,0.0);
	glutSolidCube(0.75);
	glTranslatef(0.75,0.0,0.0);
	glutSolidCube(0.75);
	glTranslatef(0.75,0.0,0.0);
	glutSolidCube(0.75);
	glTranslatef(-0.75,0.75,0.0);
	glutSolidCube(0.75);

	glPushMatrix();
	glTranslatef(0.75,-1.5,0.0);
	GLfloat x=cos(theta), y=sin(theta);
	glBegin(GL_POLYGON);
	glVertex2f(-x/2,-y/2);
	glVertex2f(-y/2,x/2);
	glVertex2f(x/2,y/2);
	glVertex2f(y/2,-x/2);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0,0.0,-0.75);
	glBegin(GL_POLYGON);
	glVertex2f(-x/2,-y/2);
	glVertex2f(-y/2,x/2);
	glVertex2f(x/2,y/2);
	glVertex2f(y/2,-x/2);
	glEnd();

	glPushMatrix();
	glTranslatef(-1.5,0.0,0.35);

	glBegin(GL_POLYGON);
	glVertex2f(-x/2,-y/2);
	glVertex2f(-y/2,x/2);
	glVertex2f(x/2,y/2);
	glVertex2f(y/2,-x/2);
	glEnd();
	
	glTranslatef(0.0,0.0,0.35);

	glBegin(GL_POLYGON);
	glVertex2f(-x/2,-y/2);
	glVertex2f(-y/2,x/2);
	glVertex2f(x/2,y/2);
	glVertex2f(y/2,-x/2);
	glEnd();


	glPopMatrix();
	glFlush();

	return;
}


void MyIdle()
{

	theta += 0.001;
	if (theta > 20000000*M_PI) theta -= 2*M_PI;
	if (i < -5){
	 	i = 2;
	}
	else{
		i -= 0.001;
	}
	glutPostRedisplay();

	return;
}

void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-2.0,2.0,-2.0,2.0,0.3,5.0);
//	glFrustum(-1.0,1.0,-1.0,1.0,9.5,12.0);
	gluPerspective(60,1.0,0.3,10.0);
	glViewport(0,0,w,h);
	return;
}

void MyRotate() {
	GLfloat u1, u2, u3, v1, v2, v3, theta, mag;
	u1=0.0;
	u2=0.0;
	u3=1.0;
	v1=1.0/ sqrt(2.0);
	v2=0.0/ sqrt(2.0);
	v3=1.0/sqrt(2.0);
	GLfloat uvi, uvj, uvk;
    uvi = u2 * v3 - v2 * u3;
    uvj = v1 * u3 - u1 * v3;
    uvk = u1 * v2 - v1 * u2;
	mag = sqrt(uvi*uvi + uvj*uvj + uvk*uvk);
	theta = asin(mag) * 180 / M_PI;
	glRotatef(theta, uvi,uvj,uvk);
	glFlush();
	return;
}



void MyKeybord(int key, int x, int y)
{

	switch(key){
	case GLUT_KEY_LEFT:
		theta +=0.1;
		i -= 0.1;
		break;	

	case GLUT_KEY_RIGHT:
		theta -=0.2;
		i += 0.2;
		break;

	case GLUT_KEY_UP:
		MyRotate();
		break;	
	}
	glutPostRedisplay();
	return;
}




int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("cube");
	// glutIdleFunc(MyIdle);
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutSpecialFunc(MyKeybord);

	glutMainLoop();
}