#include <iostream>
#include <SOIL.h>
#include <GLUT.h>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

inline float ToRad(float angle_degrees) {
	return angle_degrees * M_PI / 180.0f;
}

float xrot = 0;
float yrot = 0;
float xpos = 0;
float ypos = 0;
float zpos = 0;
bool go_forward = false, go_backward = false;
bool look_up = false, look_down = false;
bool turn_left = false, turn_right = false;
bool go_left = false, go_right = false;
GLfloat light_ambient[] = { 0.8f,0.8f,0.8f,1.0f };



GLuint texture;                                     

bool LoadGLTextures()                                    
{
	texture = SOIL_load_OGL_texture
	(
		"Textures/texture.jpg",    
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	if (texture == 0)
	{
		cout << "Error with texture.jpg..........\n";        
		return false;
	}
	else cout << "Load texture.jpg..........\n";           

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return true;  

}

static void resize(int width, int height)    
{
	const float ar = (float)width / (float)height;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

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

	float dx = cos(verticalAngle) * sin(horizontalAngle);
	float dy = sin(verticalAngle);
	float dz = cos(verticalAngle) * cos(horizontalAngle);

	float cx = xpos + dx, cy = ypos + dy, cz = zpos + dz;
	gluLookAt(xpos, ypos, zpos, cx, cy, cz, 0, 1, 0);/*mozgás, forgás vége*/
	glPushMatrix();
	glTranslatef(8.0f, 3.0f, 0.0f);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glPopMatrix();

	
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glBindTexture(GL_TEXTURE_2D, texture);          
	glBegin(GL_QUADS);                               

													 
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -4.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(6.0f, -4.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(6.0f, -4.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -4.0f, -10.0f);

	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);                   


	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, 4.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(6.0f, 4.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(6.0f, 4.0f, 10.0f);
	glTexCoord2f(0.f, 1.0f); glVertex3f(-6.0f, 4.0f, 10.0f);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -4.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-6.0f, -4.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-6.0f, 4.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, 4.0f, 10.0f);
	glEnd();
	

	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(6.0f, -4.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(6.0f, -4.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(6.0f, 4.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(6.0f, 4.0f, -10.0f);
	glEnd();


	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -4.0f, -10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(6.0f, -4.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(6.0f, 4.0f, -10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, 4.0f, -10.0f);
	glEnd();


	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(6.0f, -4.0f, 10.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-6.0f, -4.0f, 10.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-6.0f, 4.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(6.0f, 4.0f, 10.0f);
	glEnd();



	glDisable(GL_TEXTURE_2D);

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
	case  GLUT_KEY_F1:                             
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
											 
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutKeyboardUpFunc(key_release);
	glutSpecialFunc(spec);
	glutTimerFunc(0, timer, 0);

	glClearColor(0.0, 0.0, 0.0, 1);                 
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

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


	LoadGLTextures();   
	glutMainLoop();

	return 0;
}