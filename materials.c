#include <GL/gl.h>
#include <GL/glext.h>
#include <H:/glut.h>
#include <math.h>


/*
This program illustrates some 3D operations.
It draws a wire cube with sides of length 0.5 in World Coordinates.
You can uses the glOrtho or glFrustum functions
to choose either orthographic or perspective projection.
You can use the gluLookAt function to choose the viewpoint, 
view direction and the up vector.
*/

struct obj {
	float alpha;
	float beta;
	float gamma;
	float theta;
	float shiny;
	float pos;
};

struct obj constructObject(float alpha, float beta, float gamma, float theta, float shiny, float pos){
	struct obj object;
	object.alpha = alpha;
	object.beta = beta;
	object.gamma = gamma;
	object.theta = theta;
	object.shiny = shiny;
	object.pos = pos;
	return object;
}

struct obj objects[3] = {
                            {1.0, 1.0, 1.0, 2*M_PI, 5.0, 1.0},
							{2.0, 3.0, 9.0, 2*M_PI, 5.0, 2.0},
							{2.0, 3.0, 9.0, 2*M_PI, 5.0, 3.0}
                        };


void display(void)
{
	for(int i = 0; i <= sizeof(objects); i++)
	{
		struct obj object = objects[i];
		// GLfloat  ambient[4] = {0.33,0.22,0.03,1.0};
		// GLfloat diffuse[4] = {0.78,0.57,0.11,1.0};
		// GLfloat specular[4] = {0.99,0.91,0.81,1.0};
		// GLfloat shininess = object.shiny;
		// GLfloat normal[3] = {0.0,0.0,1.0};
		// GLfloat position[4] = {1.0,1.0,1.0,1.0};

		// glClearColor(0.0,0.0,1.0,1.0);

		// glClear(GL_COLOR_BUFFER_BIT);
		

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(1.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);
		
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		position[1]=cos(objects[i].theta); position[2]=sin(objects[i].theta);

		glLightfv(GL_LIGHT0, GL_POSITION, position);

		
	/*	glNormal3fv(normal);
		glBegin(GL_POLYGON);
			glVertex3f(-0.5,-0.5,0.0);
			glVertex3f(-0.5,0.5,0.0);
			glVertex3f(0.5,0.5,0.0);
			glVertex3f(0.5,-0.5,0.0);
		glEnd();
	*/
		// glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		// glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		// glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		// glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

		glPushMatrix();
		glRotatef(objects[i].alpha, 1, 0, 0); //rotate alpha around the x axis
		glRotatef(objects[i].beta, 0, 1, 0); //rotate beta around the y axis
		glutSolidCube(objects[i].pos);
		glutSwapBuffers();
		glPopMatrix();
		glFlush();
		Sleep(500);
	}
	return;
}


void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
//	glOrtho(-2.0,2.0,-2.0,2.0,-2.0,2.0);
	glFrustum(-1.0,1.0,-1.0,1.0,0.5,3.0);
	glViewport(0,0,w,h);
	return;
}

void processMenuEvents(int option) {
	for(int i = 0; i < sizeof(objects); i++){

	switch (option) {
		case 1:
			objects[i].shiny = 600.0; 
			break;
		case 2:
			objects[i].shiny=27.0; 
			break;

	}
	glutPostRedisplay();
	}
}

void MyIdle()
{
	for(int i = 0; i < sizeof(objects); i++){

		objects[i].theta += 0.001;

		if (objects[i].theta > 2*M_PI) objects[i].theta -= 2*M_PI;

		glutPostRedisplay();
	}
	return;
}

void MyRotate(int key){
	
}

void MyKeybord(int key, int x, int y)
{
	for(int i = 0; i < sizeof(objects); i++){
		switch(key){
		case GLUT_KEY_UP:
			objects[i].alpha-=5;
			break;	
		case GLUT_KEY_DOWN:
			objects[i].alpha+=5;
			break;
		case GLUT_KEY_LEFT:
			objects[i].beta-=5;
			break;
		case GLUT_KEY_RIGHT:
			objects[i].beta+=5;
			break;
		}
	glutPostRedisplay();
	}
	return;
}



int main(int argc, char **argv)
{
	int menu;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(500,200);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutIdleFunc(MyIdle);
	glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Shinier",1);
	glutAddMenuEntry("LessShiny",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutSpecialFunc(MyKeybord);

	glutMainLoop();
}