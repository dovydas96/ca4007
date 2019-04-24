#include <GL/gl.h>
#include <GL/glext.h>
#include <H:/glut.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>

float progress = 1;
GLfloat zoom = .2;
int wind_h = 500;
int wind_w = 500;
float theta = M_PI/4;

GLubyte image[64][64][3];
GLubyte image2[64][64][3];



void DrawCar(float x, float y, float z, float period) {
    
    glPushMatrix();
    
    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glMatrixMode(GL_MODELVIEW);

    
    glRotatef(360 * period * progress,0.0,0.0,1.0);
	glTranslatef(x, y, z);
	glutSolidCube(0.75);
	glTranslatef(0.0,0.75,0.0);
	glutSolidCube(0.75);
    glTranslatef(0.0,0.75,0.0);
    glutSolidCube(0.75);
    glTranslatef(0.0,-0.75,0.75);
    glutSolidCube(0.75);
    glTranslatef(0.3,-.75,-1.5);
	glRotatef(270.0, 0.0, 1.0, 0.0);
    glDisable(GL_CULL_FACE);    

    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_REPEAT);
    GLfloat x1=cos(theta), y1=sin(theta);
	glBegin(GL_POLYGON);
        glColor3f(192.0,192.0,192.0);
        glTexCoord2f(1.0,1.0);
        glVertex2f(-x1/2,-y1/2);
        glTexCoord2f(0.0,1.0);
        glVertex2f(-y1/2,x1/2);
        glTexCoord2f(0.0,0.0);
        glVertex2f(x1/2,y1/2);
        glTexCoord2f(1.0,0.0);
        glVertex2f(y1/2,-x1/2);
	glEnd();


    glTranslatef(0.0,0.0,0.6);
    glBegin(GL_POLYGON);
        glTexCoord2f(1.0,1.0);
        glVertex2f(-x1/2,-y1/2);
        glTexCoord2f(0.0,1.0);
        glVertex2f(-y1/2,x1/2);
        glTexCoord2f(0.0,0.0);
        glVertex2f(x1/2,y1/2);
        glTexCoord2f(1.0,0.0);
        glVertex2f(y1/2,-x1/2);
	glEnd();

    glTranslatef(0.0,1.5,0.0);
    glBegin(GL_POLYGON);
        glTexCoord2f(1.0,1.0);
        glVertex2f(-x1/2,-y1/2);
        glTexCoord2f(0.0,1.0);
        glVertex2f(-y1/2,x1/2);
        glTexCoord2f(0.0,0.0);
        glVertex2f(x1/2,y1/2);
        glTexCoord2f(1.0,0.0);
        glVertex2f(y1/2,-x1/2);
	glEnd();

    glTranslatef(0.0,0.0,-0.6);
    glBegin(GL_POLYGON);
        glTexCoord2f(1.0,1.0);
        glVertex2f(-x1/2,-y1/2);
        glTexCoord2f(0.0,1.0);
        glVertex2f(-y1/2,x1/2);
        glTexCoord2f(0.0,0.0);
        glVertex2f(x1/2,y1/2);
        glTexCoord2f(1.0,0.0);
        glVertex2f(y1/2,-x1/2);
	glEnd();

    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
}

void zoomy()
{
	GLsizei w = (GLsizei) wind_w;
	GLsizei h = (GLsizei) wind_h;
	float ratio = (float) w/h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, 1, -1, 1, 10);

	glViewport(0,0,w,h);
	glutPostRedisplay();
	return;
}

void display(void)
{
	glClearColor(0.0,0.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
//    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glClear(GL_DEPTH_BUFFER_BIT);

    glCullFace(GL_BACK);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0,3.0,5.0,0.0,0.0,0.0,0.0,-1.0,0.0);
	GLfloat ambient[4] ={ 0.0215, 0.1745, 0.0215, 0.55 };
	GLfloat diffuse[4] ={0.07568, 0.61424, 0.07568, 0.55 };
	GLfloat specular[4] ={0.633, 0.727811, 0.633, 0.55 };
	GLfloat shine = 76.8;
          

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32.0);


	GLUquadricObj *MyCylinder;
	MyCylinder = gluNewQuadric();
	gluQuadricDrawStyle(MyCylinder, GLU_FILL);
	
	glRotatef(-90.0,1.0,0.0,0.0);
	gluCylinder(MyCylinder,0.2,0.5,1,12,12);

    DrawCar(2, 0, 1, 1.0/10);
	zoomy();
	glFlush();
	return;
}



void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-1.0,1.0,-1.0,1.0,-1.0,1.0);
	//glFrustum(-1.0,1.0,-1.0,1.0,0.5,3.0);

	glViewport(0,0,w,h);
	return;
}

void MyIdle()
{
	progress = (progress + 0.05);

	glutPostRedisplay();
	usleep(1000000 / 30);
}

void MySpecialKeyboard (int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        progress += .05;
        theta += 0.05;
    }
    if (key == GLUT_KEY_DOWN)
    {
    	progress -= .05;
        theta -= 0.05;
    }
    if (key == GLUT_KEY_LEFT)
    {
        progress -= .05;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        progress += .05;
    }     

	glutPostRedisplay();
	return;
}

void MyKeyboard(unsigned char key, int x, int y)
{
	if (key == '+')
		zoom += .03;
	if (key == '-')
		zoom -= .03;
	zoomy();	

	glutPostRedisplay();
	return;
}

int main(int argc, char **argv)
{

    int i,j;
	FILE *fp;
	char buffer[4096],*pb;

	fp = fopen("wheele.bmp","r");
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
	glutCreateWindow("cylinder");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);

    glEnable(GL_TEXTURE_2D);
	glutSpecialFunc(MySpecialKeyboard);
	glutKeyboardFunc(MyKeyboard);
	

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glutMainLoop();
}