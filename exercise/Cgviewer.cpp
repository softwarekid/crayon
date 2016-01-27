#include "CgViewer.h"
#include <GL/glew.h>
#include <GL/glut.h>
using namespace std;

CgViewer::CgViewer(const char* title, int width, int height, float lightAngle, bool isAnimating):
         GlutWrapper(title, width, height, lightAngle)
{
    _isAnimating = isAnimating;
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
        cgDestroyContext(context);
        exit(0);
        break;
    }
}

