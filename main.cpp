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
    GLdouble dRadius = 0.1; // Initial radius of spiral
    GLdouble dAngle;        // Looping variable
            
    // Clear blue window
    glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
        
    // Use 0 for clear stencil, enable stencil test
    glClearStencil(0.0f);
    glEnable(GL_STENCIL_TEST);

    // Clear color and stencil buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
                
    // All drawing commands fail the stencil test, and are not
    // drawn, but increment the value in the stencil buffer. 
    glStencilFunc(GL_NEVER, 0x0, 0x0);
    glStencilOp(GL_INCR, GL_INCR, GL_INCR);

    // Spiral pattern will create stencil pattern
    // Draw the spiral pattern with white lines. We 
    // make the lines  white to demonstrate that the 
    // stencil function prevents them from being drawn
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for(dAngle = 0; dAngle < 400.0; dAngle += 0.1) {
        glVertex2d(dRadius * cos(dAngle), dRadius * sin(dAngle));
        dRadius *= 1.002;
    }
    glEnd();
            
    // Now, allow drawing, except where the stencil pattern is 0x1
    // and do not make any further changes to the stencil buffer
    glStencilFunc(GL_NOTEQUAL, 0x1, 0x1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        
    // Now draw red bouncing square
    // (x and y) are modified by a timer function
    glColor3f(1.0f, 0.0f, 0.0f);
    glRectf(x, y, x + rsize, y - rsize);
    
    // All done, do the buffer swap
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
    const GLfloat BORDER = 100.f;

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

void TimerFunction(int value)
{
    // Reverse direction when you reach left or right edge
    if(x > windowWidth-rsize || x < -windowWidth)
        xstep = -xstep;

    // Reverse direction when you reach top or bottom edge
    if(y > windowHeight || y < -windowHeight + rsize)
        ystep = -ystep;


    // Check bounds. This is in case the window is made
    // smaller while the rectangle is bouncing and the 
	// rectangle suddenly finds itself outside the new
    // clipping volume
    if(x > windowWidth-rsize)
        x = windowWidth-rsize-1;

    if(y > windowHeight)
        y = windowHeight-1; 

	// Actually move the square
    x += xstep;
    y += ystep;

     // Redraw the scene with new coordinates
    glutPostRedisplay();
    glutTimerFunc(33,TimerFunction, 1);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(
         GLUT_RGB
        | GLUT_DOUBLE
        | GLUT_STENCIL
        //| GLUT_DEPTH
    );
    glutCreateWindow("Sample");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    //SetupRC();
    glutTimerFunc(33,TimerFunction, 0);
    glutMainLoop();
    return 0;
}
