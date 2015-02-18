#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/glext.h>
#include <math.h>
#include "OptionsReader.h"
#define GL_PI 3.1415f

// Initial square position and size
GLfloat x = 0.0f;
GLfloat y = 0.0f;
GLfloat rsize = 25;

// Step size in x and y directions
// (number of pixels to move each time)
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat xRot = 0.f;
GLfloat yRot = 0.f;

// Keep track of windows changing width and height
GLfloat windowWidth;
GLfloat windowHeight;
void RenderScene()
{
	// Angle of revolution around the nucleus
	static GLfloat fElect1 = 0.0f;

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset the modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Translate the whole scene out and into view	
	// This is the initial viewing transformation
	glTranslatef(0.0f, 0.0f, -100.0f);	

	// Red Nucleus
	glColor3ub(255, 0, 0);
	glutSolidSphere(10.0f, 15, 15);

	// Yellow Electrons
	glColor3ub(255,255,0);

	// First Electron Orbit
	// Save viewing transformation
	glPushMatrix();

	// Rotate by angle of revolution
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);

	// Translate out from origin to orbit distance
	glTranslatef(90.0f, 0.0f, 0.0f);

	// Draw the electron
	glutSolidSphere(6.0f, 15, 15);
    

	// Restore the viewing transformation
	glPopMatrix();

	// Second Electron Orbit
	glPushMatrix();
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-70.0f, 0.0f, 0.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();


	// Third Electron Orbit
	glPushMatrix();
	glRotatef(360.0f-45.0f,0.0f, 0.0f, 1.0f);
	glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, 60.0f);
	glutSolidSphere(6.0f, 15, 15);
	glPopMatrix();


	// Increment the angle of revolution
	fElect1 += 10.0f;
	if(fElect1 > 360.0f)
		fElect1 = 0.0f;

	// Show the image
	glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y)
{
    //std::cout << "key pressed: " << key << std::endl;
    switch (key) {
        case 'a':
            xRot -= 5;
            break;
        case 'd':
            xRot += 5;
            break;
        case 's':
            yRot -= 5;
            break;
        case 'w':
            yRot += 5;
            break;
    }
    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y)
{
    //std::cout << "key up: " << key << std::endl;
}

void ChangeSize(GLsizei width, GLsizei height)
{
    if( height == 0 ){
        height = 1;
    }
    const GLfloat ASPECT_RATIO = (GLfloat)width / (GLfloat)height;

    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );            // Выбор матрицы проекций
    glLoadIdentity();              // Сброс матрицы проекции
    // Вычисление соотношения геометрических размеров для окна
    gluPerspective( 100.0f, ASPECT_RATIO, 10.f, 500.0f );
    //
    const GLfloat BORDER = 200.f;

    //if (width <= height) {
        //glOrtho(-BORDER [> left */, BORDER /* right <],
                //-BORDER / ASPECT_RATIO [> bottom */, BORDER / ASPECT_RATIO /* top <],
                //-BORDER [> near */, BORDER /* far <]);
    //}
    //else {
        //glOrtho(-BORDER * ASPECT_RATIO [> left */, BORDER * ASPECT_RATIO /* right <],
                //-BORDER [> back */, BORDER /* front <],
                //-BORDER [> near */, BORDER/* far <]);
    //}

    glMatrixMode( GL_MODELVIEW );   // Выбор матрицы вида модели
    glTranslatef(0.0f, 0.0f, 250.0f);
    glLoadIdentity();               // Сброс матрицы вида модели
}

void SetupRC()
{
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	
}

void TimerFunction(int value)
{
    glutPostRedisplay();
    glutTimerFunc(100, TimerFunction, 1);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(
         GLUT_RGB
        | GLUT_DOUBLE
        //| GLUT_STENCIL
        | GLUT_DEPTH
    );
    glutCreateWindow("Sample");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    SetupRC();
    glutTimerFunc(500,TimerFunction, 0);
    glutMainLoop();
    return 0;
}
