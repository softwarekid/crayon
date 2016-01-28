#include "CgViewer.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "Constants.h"
using namespace std;

CgViewer::CgViewer(const char* title, int width, int height, float lightAngle):
         GlutWrapper(title, width, height)
{
    _lightAngle = lightAngle;
}

void CgViewer::_Keyboard(int c, int x, int y)
{
    switch (c)
    {
    case 'p':
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutPostRedisplay();
        break;
    case 'l':
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glutPostRedisplay();
        break;
    case 27:  /* Esc key */
        /* Demonstrate proper deallocation of Cg runtime data structures.
        Not strictly necessary if we are simply going to exit. */
        _exit();
        break;
    }
}

void CgViewer::_Idle()
{
    _lightAngle += 0.008;
    if(_lightAngle > 2 * Constants::Math::PI)
    {
        _lightAngle -= 2 * Constants::Math::PI;
    }
    glutPostRedisplay();
}

void CgViewer::_Reshape(int width, int height)
{
    float aspectRatio = (float)width / (float) height;
    float fov = 40.0f;
    _transform.SetProjection(fov,aspectRatio,1.0, 20.0);
    glViewport(0, 0, width, height);
}
