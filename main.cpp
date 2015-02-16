#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/glext.h>
#include <math.h>
#include "OptionsReader.h"
#define GL_PI 3.1415f

OptionReader * OptionReader::_self = nullptr;
auto options = OptionReader::getSingleton()->getOptions();
bool bCull = (options["bCull"] == "1");
bool bDepth = (options["bDepth"] == "1");
bool bOutline = (options["bOutline"] == "1");
GLfloat xRot = 45.0, yRot = 45.0;
GLubyte fire[128] = { 0x00, 0x00, 0x00, 0x00, 
				   0x00, 0x00, 0x00, 0x00,
				   0x00, 0x00, 0x00, 0x00,
				   0x00, 0x00, 0x00, 0x00,
				   0x00, 0x00, 0x00, 0x00,
				   0x00, 0x00, 0x00, 0x00,
				   0x00, 0x00, 0x00, 0xc0,
				   0x00, 0x00, 0x01, 0xf0,
				   0x00, 0x00, 0x07, 0xf0,
				   0x0f, 0x00, 0x1f, 0xe0,
				   0x1f, 0x80, 0x1f, 0xc0,
				   0x0f, 0xc0, 0x3f, 0x80,	
				   0x07, 0xe0, 0x7e, 0x00,
				   0x03, 0xf0, 0xff, 0x80,
				   0x03, 0xf5, 0xff, 0xe0,
				   0x07, 0xfd, 0xff, 0xf8,
				   0x1f, 0xfc, 0xff, 0xe8,
				   0xff, 0xe3, 0xbf, 0x70, 
				   0xde, 0x80, 0xb7, 0x00,
				   0x71, 0x10, 0x4a, 0x80,
				   0x03, 0x10, 0x4e, 0x40,
				   0x02, 0x88, 0x8c, 0x20,
				   0x05, 0x05, 0x04, 0x40,
				   0x02, 0x82, 0x14, 0x40,
				   0x02, 0x40, 0x10, 0x80, 
				   0x02, 0x64, 0x1a, 0x80,
				   0x00, 0x92, 0x29, 0x00,
				   0x00, 0xb0, 0x48, 0x00,
				   0x00, 0xc8, 0x90, 0x00,
				   0x00, 0x85, 0x10, 0x00,
				   0x00, 0x03, 0x00, 0x00,
				   0x00, 0x00, 0x10, 0x00 };

void RenderScene()
{
	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT);

	// Save matrix state and do the rotation
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	// Begin the stop sign shape,
	// use a standard polygon for simplicity
	glBegin(GL_POLYGON);
		glVertex2f(-20.0f, 50.0f);
		glVertex2f(20.0f, 50.0f);
		glVertex2f(50.0f, 20.0f);
		glVertex2f(50.0f, -20.0f);
		glVertex2f(20.0f, -50.0f);
		glVertex2f(-20.0f, -50.0f);
		glVertex2f(-50.0f, -20.0f);
		glVertex2f(-50.0f, 20.0f);
	glEnd();

	// Restore transformations
	glPopMatrix();

	// Flush drawing commands
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
    RenderScene();
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
    //gluPerspective( 45.0f, ASPECT_RATIO, 10.f, 100.0f );
    //
    const GLfloat BORDER = 100.;

    if (width <= height) {
        glOrtho(-BORDER /* left */, BORDER /* right */,
                -BORDER / ASPECT_RATIO /* bottom */, BORDER / ASPECT_RATIO /* top */,
                -BORDER /* near */, BORDER /* far */);
    }
    else {
        glOrtho(-BORDER * ASPECT_RATIO /* left */, BORDER * ASPECT_RATIO /* right */,
                -BORDER /* back */, BORDER /* front */,
                -BORDER /* near */, BORDER/* far */);
    }

    glMatrixMode( GL_MODELVIEW );   // Выбор матрицы вида модели
    glLoadIdentity();               // Сброс матрицы вида модели
}

void SetupRC()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

	// Set drawing color to red
	glColor3f(1.0f, 0.0f, 0.0f);
	
	// Enable polygon stippling
	glEnable(GL_POLYGON_STIPPLE);
	
	// Specify a specific stipple pattern
	glPolygonStipple(fire);
}

int main(int argc, char *argv[])
{
    std::cout <<
        bCull << std::endl <<
        bDepth << std::endl <<
        bOutline << std::endl;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Sample");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    SetupRC();
    glutMainLoop();
    return 0;
}
