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

void RenderScene()
{
    GLfloat x,y,z,angle;
    //GLfloat xRot = 0.0, yRot = 0.0;
    int iPivot = 1;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (bCull)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);

    if (bDepth) {
        glEnable(GL_DEPTH_TEST);
    }
    else {
        glDisable(GL_DEPTH_TEST);
    }

    if (bOutline)
        glPolygonMode(GL_BACK, GL_LINE);
    else
        glPolygonMode(GL_BACK, GL_FILL);

    glPushMatrix();
    glRotatef(xRot, 1., 0., 0.);
    glRotatef(yRot, 0., 1., 0.);

    //z = -50.;
    //glEnable(GL_LINE_STIPPLE);
    //GLint factor = 1;
    //GLushort pattern = 0x11ff;  // OpenGL superbook p. 130.
    //glLineStipple(factor, pattern);
    glBegin(GL_TRIANGLE_FAN);
    {
        glVertex3f(0.f,0.f,75.f);
        for (angle = 0.; angle <= (2.f*GL_PI); angle += (GL_PI/8.f)) {
            x = 50.f * sin(angle);
            y = 50.f * cos(angle);

            if (iPivot % 2 == 0) {
                glColor3f(0.f, 1.f, 0.f);
            }
            else{
                glColor3f(1.f, 0.f, 0.f);
            }
            ++iPivot;
            glVertex3f(x,y,0.f);
        }
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    {
        glVertex3f(0.f,0.f,0.f);
        for (angle = 0.; angle <= (2.f*GL_PI); angle += (GL_PI/8.f)) {
            x = 50.f * sin(angle);
            y = 50.f * cos(angle);

            if (iPivot % 2 == 0) {
                glColor3f(0.f, 1.f, 0.f);
            }
            else{
                glColor3f(1.f, 0.f, 0.f);
            }
            ++iPivot;
            glVertex3f(x,y,0.f);
        }
    }
    glEnd();

    glPopMatrix();
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
    glClearColor(0., 0., 0., 1.);
    glColor3f(0., 1., 0.);
    glShadeModel( GL_FLAT );
    //glClearDepth( 1.0f );              // Разрешить очистку буфера глубины
    //glEnable( GL_DEPTH_TEST );            // Разрешить тест глубины
    //glDepthFunc( GL_LEQUAL );            // Тип теста глубины
    glFrontFace(GL_CW);
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
