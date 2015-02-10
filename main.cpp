#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <math.h>
#define GL_PI 3.1415f

void RenderScene()
{
    GLfloat x,y,z,angle;
    GLfloat xRot = 0.0, yRot = 0.0;


    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glRotatef(xRot, 1., 0., 0.);
    glRotatef(yRot, 0., 1., 0.);
    z = 0.;
    glBegin(GL_LINES);
    {
        for (angle = 0.; angle <= GL_PI; angle += (GL_PI/20.0f)) {
            x = 50.f * sin(angle);
            y = 50.f * cos(angle);
            glVertex3f(x,y,z);

            x = 50.f * sin(angle+GL_PI);
            y = 50.f * cos(angle+GL_PI);
            glVertex3f(x,y,z);
        }
    }
    glEnd();
    glPopMatrix();
    glutSwapBuffers();
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
    //gluPerspective( 45.0f, ASPECT_RATIO, 0.1f, 100.0f );
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
    glShadeModel( GL_SMOOTH );
    glClearDepth( 1.0f );              // Разрешить очистку буфера глубины
    glColor3f(0., 1., 0.);
    glEnable( GL_DEPTH_TEST );            // Разрешить тест глубины
    glDepthFunc( GL_LEQUAL );            // Тип теста глубины
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Sample");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();
    glutMainLoop();
    return 0;
}
