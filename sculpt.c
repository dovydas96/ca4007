#include <GL/gl.h>
#include <GL/glext.h>
#include <H:/glut.h>
#include <math.h>
#include <stdio.h>


float theta = M_PI/4;
float alpha = 1.0;
float beta  = 1.0;
float shiny = 27.0;
float view = 3.0;

int curr_pos = -1;
float state = 0.0;
float state2 = 0.0;

int coords[64];
int totalCubes=0;

int MENU_ENTRY_INDEX = 2; //0 -> exit, 1 -> clear
enum { SUB_SUBMENU_ENTRIES = 5 };
char *colours[SUB_SUBMENU_ENTRIES] = {"Red", "Green", "Blue", "Yellow","Transparent"};
int submenus_colors_cube[SUB_SUBMENU_ENTRIES];
int submenus_colors_teapot[SUB_SUBMENU_ENTRIES];
int submenus_colors_sphere[SUB_SUBMENU_ENTRIES];



int selected_colour = 1;    //1 - red, 2 - green, 3 - blue, 4 - Material, 5 - transparent
int selected_size = 1;      //1 - 0.05, 2 - 0.1, 3 - 0.3, 4 - 0.5, 5 - 1.0
int selected_shape = 1;     //1 - cube, 2 - sphere 3 - teapot

int shape_types[256];
int shape_colors[256];
float shape_sizes[256];

int stateBool = 0;

GLubyte image[480][480][3]; 

void display(void)
{

		glClearColor(0.0,0.0,1.0,0.0);
		glClear(GL_COLOR_BUFFER_BIT);

		GLfloat  ambient[4] = {0.33,0.22,0.03,1.0};
		GLfloat diffuse[4] = {0.78,0.57,0.11,1.0};
		GLfloat specular[4] = {0.99,0.91,0.81,1.0};
		GLfloat shininess = 27.3;
		GLfloat normal[3] = {0.0,0.0,1.0};
		GLfloat position[4] = {1.0,1.0,1.0,1.0};
		

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(0.0,0.0,view,0.0,0.0,0.0,0.0,1.0,0.0);
		
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

        glEnable(GL_TEXTURE_2D);


		position[1]=cos(theta); position[2]=sin(theta);

		glLightfv(GL_LIGHT0, GL_POSITION, position);


        for(int i = 0;i < totalCubes;i++){

			GLfloat mat_colour[4] = {0.0, 0.0, 1.0, 1.0};

			if(shape_colors[i] == 1) { mat_colour[0] = 1.0; }
			else if(shape_colors[i] == 2) { mat_colour[1] = 1.0; }
			else if(shape_colors[i] == 3) { mat_colour[2] = 1.0; }
			else if(shape_colors[i] == 4) { mat_colour[0] = 1.0; mat_colour[1] = 1.0; }

            GLfloat x = ((coords[i*2]-250.0))/250.0;
            GLfloat y =	-(coords[i*2 + 1]-250.0)/250.0;


			// glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);
			// glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_colour);
			// glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_colour);
			// glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_colour);
			// glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 32.0);


            glPushMatrix();
            glRotatef(alpha, 1, 0, 0); //rotate alpha around the x axis
		    glRotatef(beta, 0, 1, 0); //rotate beta around the y axis
            glTranslatef(x, y, 0.0);
			
        	if(shape_types[i] == 1)
            	if(shape_colors[i] == 5)
                	glutWireCube(shape_sizes[i]);
            	else
                	glutSolidCube(shape_sizes[i]);
       		else if(shape_types[i] == 3)
            	if(shape_colors[i] == 5)
                	glutWireTeapot(shape_sizes[i]);
            	else
                	glutSolidTeapot(shape_sizes[i]);
            else if(shape_types[i] == 2){
                glEnable(GL_TEXTURE_2D);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 64, 64, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

                GLUquadricObj *MySphere;
                MySphere = gluNewQuadric();
                gluQuadricTexture(MySphere,1);
                gluSphere(MySphere,0.5,24,24);
                glDisable(GL_TEXTURE_2D);

            }

            glPopMatrix();


        }
	    glutSwapBuffers();
		glFlush();
	return;
}


void MyReshape(GLsizei w, GLsizei h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-2.0,2.0,-2.0,2.0,0.3,5.0);
	glFrustum(-1.0,1.0,-1.0,1.0,2.5,5.0);
	// gluPerspective(60,1.0,0.3,10.0);
	glViewport(0,0,w,h);
	return;
}


void processMenuEvents(int option) {
	switch (option){
		case 0:exit(0);
		case 1: totalCubes = 0; break;
		
		case 2: selected_colour = 1;  selected_shape = 1; break;
        case 3: selected_colour = 2;  selected_shape = 1; break;
        case 4: selected_colour = 3;  selected_shape = 1; break;
        case 5: selected_colour = 4;  selected_shape = 1; break;
        case 6: selected_colour = 5;  selected_shape = 1; break;

		case 7: selected_colour = 1;  selected_shape = 2; break;
        case 8: selected_colour = 2;  selected_shape = 2; break;
        case 9: selected_colour = 3;  selected_shape = 2; break;
        case 10: selected_colour = 4;  selected_shape = 2; break;
        case 11: selected_colour = 5;  selected_shape = 2; break;

		case 12: selected_colour = 1;  selected_shape = 3; break;
        case 13: selected_colour = 2;  selected_shape = 3; break;
        case 14: selected_colour = 3;  selected_shape = 3; break;
        case 15: selected_colour = 4;  selected_shape = 3; break;
        case 16: selected_colour = 5;  selected_shape = 3; break;

	}
	return;
}

void createGLUTMenus() {
    //colours / materials for shapes

    //sizes for shapes
    int submenu_sizes_cube = glutCreateMenu(processMenuEvents);
    for(int i = 0; i < SUB_SUBMENU_ENTRIES; i++)
        glutAddMenuEntry(colours[i], MENU_ENTRY_INDEX++);
    
    int submenu_sizes_sphere = glutCreateMenu(processMenuEvents);
    for(int i = 0; i < SUB_SUBMENU_ENTRIES; i++)
        glutAddMenuEntry(colours[i], MENU_ENTRY_INDEX++);

    int submenu_sizes_teapot = glutCreateMenu(processMenuEvents);
    for(int i = 0; i < SUB_SUBMENU_ENTRIES; i++)
        glutAddMenuEntry(colours[i], MENU_ENTRY_INDEX++);

    
    int menu_id = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("Clear", 1);
    glutAddSubMenu("Insert Cube", submenu_sizes_cube);
    glutAddSubMenu("Insert Teapot", submenu_sizes_teapot);
	glutAddSubMenu("Insert Sphere", submenu_sizes_sphere);

    glutAddMenuEntry("Quit", 0);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void MyIdle()
{
		theta += 0.001;
		if (theta > 2*M_PI) theta -= 2*M_PI;
		glutPostRedisplay();
	return;
}


void MyKeybord(int key, int x, int y)
{

		switch(key){
		case GLUT_KEY_UP:
			alpha-=5;
			break;	
		case GLUT_KEY_DOWN:
			alpha+=5;
			break;
		case GLUT_KEY_LEFT:
			beta-=5;
			break;
		case GLUT_KEY_RIGHT:
			beta+=5;
			break;
		case GLUT_KEY_F1:
			view+=.1;
			break;
		case GLUT_KEY_F2:
			view-=0.1;
			break;

		case GLUT_KEY_F3:
			shape_sizes[curr_pos] += .1;
			break;

		case GLUT_KEY_F4:
			shape_sizes[curr_pos] -= .1;
			break;
		}

	glutPostRedisplay();
	return;
}

void mouseClicks(int button, int mouseState, int x, int y) {

    if(button == GLUT_LEFT_BUTTON && mouseState == GLUT_DOWN) {
		printf("x: %d, y: %d totalCubes: %d \n", x, y, totalCubes);
		coords[totalCubes*2] = x;
		coords[totalCubes*2 + 1] = y;
		shape_types[totalCubes] = selected_shape;
        shape_colors[totalCubes] = selected_colour;
		shape_sizes[totalCubes] = 0.5;
		curr_pos ++;
		totalCubes++;
		glutPostRedisplay();
    }
}




int main(int argc, char **argv)
{
    int i,j;
	FILE *fp;
	char buffer[221184],*pb;

	fp = fopen("texture.bin","r");
	fread(buffer, 221184,1,fp);

	pb = buffer;

	for(i=0; i<480; i++)
	   for(j=0; j<480; j++)
		{		
		image[i][j][0]=(GLubyte)*pb;
		image[i][j][1]=(GLubyte)*pb;
		image[i][j][2]=(GLubyte)*pb;
		pb++;
		}

	int menu;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,65);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutReshapeFunc(MyReshape);
	glutIdleFunc(MyIdle);
	createGLUTMenus();
	glutSpecialFunc(MyKeybord);
    glutMouseFunc(mouseClicks);

	glutMainLoop();
}
