#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glext.h>

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.,0.,0.);
    glRectf(-25.,25.,25.,-25.);
    glFlush();
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

    if (width <= height) {
        glOrtho(-100. /* left */, 100. /* right */,
                -100 / ASPECT_RATIO /* bottom */, 100 / ASPECT_RATIO /* top */,
                -1. /* near */, 1./* far */);
    }
    else {
        glOrtho(-100 * ASPECT_RATIO /* left */, 100 * ASPECT_RATIO /* right */,
                -100. /* back */, 100. /* front */,
                -1. /* near */, 1./* far */);
    }

    glMatrixMode( GL_MODELVIEW );   // Выбор матрицы вида модели
    glLoadIdentity();               // Сброс матрицы вида модели
}

void SetupRC()
{
    glClearColor(0., 0., 0., 1.);

    glShadeModel( GL_SMOOTH );

    glClearDepth( 1.0f );              // Разрешить очистку буфера глубины
    glEnable( GL_DEPTH_TEST );            // Разрешить тест глубины
    glDepthFunc( GL_LEQUAL );            // Тип теста глубины
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Sample");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    SetupRC();
    glutMainLoop();
    return 0;
}
