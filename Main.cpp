#include "Calcs3D.h"
#include <iostream>
#include <GLUT.h>

using namespace std;

inline float ToRad(float angle_degrees) {
	return angle_degrees * M_PI / 180.0f;
}

float xrot = 0;
float yrot = 0;
float xpos = 0;
float ypos = 0.5;
float zpos = -2;
bool go_forward = false, go_backward = false;
bool look_up = false, look_down = false;
bool turn_left = false, turn_right = false;
bool go_left = false, go_right = false;

float dx, dy, dz;
float cx, cy, cz;
bool tUp = false, tDown = false, tLeft = false, tRight = false;

GLfloat light_ambient[] = { 0.8f,0.8f,0.8f,1.0f };

Vec3 Triangle[3];
Vec3 Triangle2[3];
Vec3 Line[2];

bool bCollided;
Calcs3D Math;

GLuint texture;                                     

void Init()
{
	Triangle[0].x = -1.0f;
	Triangle[0].y = 0.0f;
	Triangle[0].z = 0.0f;

	Triangle[1].x = 1.0f;
	Triangle[1].y = 0.0f;
	Triangle[1].z = 0.0f;

	Triangle[2].x = 0.0f;
	Triangle[2].y = 1.0f;
	Triangle[2].z = 0.0f;

	Triangle2[0].x = -5.0f;
	Triangle2[0].y = 0.0f;
	Triangle2[0].z = 10.0f;

	Triangle2[1].x = 5.0f;
	Triangle2[1].y = 0.0f;
	Triangle2[1].z = 10.0f;

	Triangle2[2].x = 0.0f;
	Triangle2[2].y = 5.0f;
	Triangle2[2].z = 10.0f;

	Line[0].x = xpos;
	Line[0].y = 0.3f;
	Line[0].z = zpos;

	Line[1].x = 0.0f;
	Line[1].y = 0.5f;
	Line[1].z = 0.0f;

}


static void resize(int width, int height)    
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.01f, 100.0f);

	glMatrixMode(GL_MODELVIEW);


}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 0);
	if (go_forward == true) {
		xpos += (float)sin(yrot*3.14f / 180.0f) * 0.2f;
		zpos += (float)cos(yrot*3.14f / 180.0f) * 0.2f;
	}
	if (go_backward == true) {
		xpos -= (float)sin(yrot*3.14f / 180.0f) * 0.2f;
		zpos -= (float)cos(yrot*3.14f / 180.0f) * 0.2f;
	}
	if (go_left == true) {
		xpos += (float)cos(yrot*3.14f / 180.0f) * 0.15f;
		zpos += (float)sin(yrot*3.14f / 180.0f) * -0.15f;
	}
	if (go_right == true) {
		xpos -= (float)cos(yrot*3.14f / 180.0f) * 0.15f;
		zpos -= (float)sin(yrot*3.14f / 180.0f) * -0.15f;
	}
	cout << "\nPOZI: Xpos: " << xpos << ", Ypos: " << ypos << ", Zpos: " << zpos << "\n";

	Line[0].x = xpos;
	Line[0].y = ypos - 0.01f;
	Line[0].z = zpos;
	cout << "P1: Xpos: " << Line[0].x << ", Ypos: " << Line[0].y << ", Zpos: " << Line[0].z << "\n";

	Line[1].x = xpos + (dx * 500);
	Line[1].y = ypos + (dy * 500);
	Line[1].z = zpos + (dz * 500);
	cout << "P2: Xpos: " << Line[1].x << ", Ypos: " << Line[1].y << ", Zpos: " << Line[1].z << "\n";

	if (look_up == true) {
		if (xrot >= 87.0f) {
			xrot = 87.0f;
		}
		else {
			xrot += 2.0f;
		}
	}

	if (look_down == true) {
		if (xrot <= -87.0f) {
			xrot = -87.0f;
		}
		else {
			xrot -= 2.0f;
		}
	}
	if (turn_left == true) {
		yrot += 2.0f;
	}
	if (turn_right == true) {
		yrot -= 2.0f;
	}

	if (tUp)
	{
		Line[0].y += 0.05f;
		Line[1].y += 0.05f;
	}
	if (tDown)
	{
		Line[0].y -= 0.05f;
		Line[1].y -= 0.05f;
	}
	if (tLeft)
	{
		Line[0].x += 0.05f;
		Line[1].x += 0.05f;
	}
	if (tRight)
	{
     	Line[0].x -= 0.05f;
		Line[1].x -= 0.05f;
	}
}


static void display(void)                
{

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	float sceneroty = 360.0f - yrot;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_2D);
	/*mozgás, forgás*/glMatrixMode(GL_MODELVIEW);
	float verticalAngle = ToRad(xrot);
	float horizontalAngle = ToRad(yrot);

	dx = cos(verticalAngle) * sin(horizontalAngle);
	dy = sin(verticalAngle);
	dz = cos(verticalAngle) * cos(horizontalAngle);

	float a = 0, b = 1, c = 0;

	cx = xpos + dx, cy = ypos + dy, cz = zpos + dz;

	cout << "IRANY: CX: " << cx << ", CY: " << cy << ", CZ: " << cz << "\n";
	gluLookAt(xpos, ypos, zpos, cx, cy, cz, a, b, c);/*mozgás, forgás vége*/

	glPushMatrix();
	glTranslatef(8.0f, 3.0f, 0.0f);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glPopMatrix();

	bCollided = Math.IntersectedPolygon(Triangle, Line, 3);
	bool bCollided2 = Math.IntersectedPolygon(Triangle2, Line, 3);

	glBegin(GL_TRIANGLES);
	if (bCollided)
		glColor3ub(0, 255, 0);
	else
		glColor3ub(255, 0, 0);
	glVertex3f(Triangle[0].x, Triangle[0].y, Triangle[0].z);
						
	glVertex3f(Triangle[1].x, Triangle[1].y, Triangle[1].z);
						
	glVertex3f(Triangle[2].x, Triangle[2].y, Triangle[2].z);
	glEnd();

	glBegin(GL_TRIANGLES);
	if (bCollided2)
		glColor3ub(0, 255, 0);
	else
		glColor3ub(255, 0, 0);
	glVertex3f(Triangle2[0].x, Triangle2[0].y, Triangle2[0].z);

	glVertex3f(Triangle2[1].x, Triangle2[1].y, Triangle2[1].z);

	glVertex3f(Triangle2[2].x, Triangle2[2].y, Triangle2[2].z);
	glEnd();

	glLineWidth(5);
	glBegin(GL_LINES);	
	glColor3ub(255, 255, 255);
	glVertex3f(Line[0].x, Line[0].y, Line[0].z);
	glVertex3f(Line[1].x, Line[1].y, Line[1].z);
	glEnd();


	glutSwapBuffers();                


}

static void key(unsigned char key, int x, int y)
{
	switch (key)
	{
		
	case 'w':                                     
		go_forward = true;
		break;

	case 's':                   
		go_backward = true;
		break;

	case 'a':
		go_left = true;
		break;

	case 'd':
		go_right = true;
		break;

	case '4':                                        
		turn_left = true;
		break;
	case '6':                                        
		turn_right = true;
		break;
	case '8':
		look_up = true;
		break;
	case '5':
		look_down = true;
		break;
	}

	glutPostRedisplay();           
}

static void key_release(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'w':
		go_forward = false;
		break;

	case 's':
		go_backward = false;
		break;

	case 'a':
		go_left = false;
		break;

	case 'd':
		go_right = false;
		break;

	case '4':
		turn_left = false;
		break;
	case '6':
		turn_right = false;
		break;
	case '8':
		look_up = false;
		break;
	case '5':
		look_down = false;
		break;
	}

	glutPostRedisplay();
}

static void spec(int key, int x, int y) {              
	switch (key) {
	case  GLUT_KEY_UP:
		tUp = true;
		break;
	case GLUT_KEY_DOWN:
		tDown = true;
		break;
	case  GLUT_KEY_LEFT:
		tLeft = true;
		break;
	case GLUT_KEY_RIGHT:
		tRight = true;
		break;
	}
	glutPostRedisplay();
}

static void specUp(int key, int x, int y) {
	switch (key) {
	case  GLUT_KEY_UP:
		tUp = false;
		break;
	case GLUT_KEY_DOWN:
		tDown = false;
		break;
	case  GLUT_KEY_LEFT:
		tLeft = false;
		break;
	case GLUT_KEY_RIGHT:
		tRight = false;
		break;
	}
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(1280, 720);                 
	glutInitWindowPosition(100, 100);              
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_ALPHA);

	glutCreateWindow("Bullet");         
								
	Init();

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(key_release);
	glutSpecialFunc(spec);
	glutSpecialUpFunc(specUp);
	glutTimerFunc(0, timer, 0);

	glClearColor(0.0, 0.0, 0.0, 1);                 

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_LESS);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	GLfloat material[] = { 0.5,0.5,0.5,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material);


	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_ambient);

	glutMainLoop();

	return 0;
}