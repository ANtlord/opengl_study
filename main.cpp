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
//bool bCull = (options["bCull"] == "1");
//bool bDepth = (options["bDepth"] == "1");
//bool bOutline = (options["bOutline"] == "1");
GLfloat xRot = 45.0, yRot = 45.0;

auto iMode = (options["iMode"]);
GLboolean bEdgeFlag = GL_TRUE;
void RenderScene()
{
	// Clear the window
	glClear(GL_COLOR_BUFFER_BIT);


	// Draw back side as a polygon only, if flag is set
	if(iMode == "1")
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

	if(iMode == "2")
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);

	if(iMode == "3")
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);


	// Save matrix state and do the rotation
	glPushMatrix();
	glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glRotatef(yRot, 0.0f, 1.0f, 0.0f);


	// Begin the triangles
	glBegin(GL_TRIANGLES);

		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.0f, 0.0f);
		glEdgeFlag(GL_TRUE);
		glVertex2f(20.0f, 0.0f);
		glVertex2f(0.0f, 40.0f);

		glVertex2f(-20.0f,0.0f);
		glVertex2f(-60.0f,-20.0f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.0f,-40.0f);
		glEdgeFlag(GL_TRUE);

		glVertex2f(-20.0f,-40.0f);
		glVertex2f(0.0f, -80.0f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(20.0f, -40.0f);
		glEdgeFlag(GL_TRUE);

		glVertex2f(20.0f, -40.0f);
		glVertex2f(60.0f, -20.0f);
		glEdgeFlag(bEdgeFlag);
		glVertex2f(20.0f, 0.0f);
		glEdgeFlag(GL_TRUE);

		// Center square as two triangles
		glEdgeFlag(bEdgeFlag);
		glVertex2f(-20.0f, 0.0f);
		glVertex2f(-20.0f,-40.0f);
		glVertex2f(20.0f, 0.0f);

		glVertex2f(-20.0f,-40.0f);
		glVertex2f(20.0f, -40.0f);
		glVertex2f(20.0f, 0.0f);
		glEdgeFlag(GL_TRUE);

	// Done drawing Triangles
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

	// Set drawing color to green
	glColor3f(0.0f, 1.0f, 0.0f);
}

int main(int argc, char *argv[])
{
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
