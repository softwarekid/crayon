#include "GlutWrapper.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include <iostream>

void GlutWrapper::keyboard(unsigned char c, int x, int y)
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
    case ' ':
        //animating = !animating; /* Toggle */
        //if (animating)
        {
            glutIdleFunc(_idle);
        }
        //else 
        {
            glutIdleFunc(nullptr);
        }    
        break;
    case 27:  /* Esc key */
        /* Demonstrate proper deallocation of Cg runtime data structures.
        Not strictly necessary if we are simply going to exit. */
        //cgDestroyProgram(programVertex);
        //cgDestroyContext(context);
        exit(0);
        break;
    }
}

void GlutWrapper::_idle()
{

}

void GlutWrapper::_display()
{
    Matrix4f MVPMatrix;
    transform.GetMVPMatrix(MVPMatrix);
    verShader.SetMVPParam(MVPMatrix);

    if(mesh.GetVertexCount() == 0)
    {
        glutSolidTeapot(2.0);
        //glutSolidSphere(2.0, 10, 10);
    }
}

void GlutWrapper::requestSynchronizedSwapBuffers()
{
#ifdef _WIN32
    if(wglSwapIntervalEXT)
    {
        wglSwapIntervalEXT(1);
    }
#endif
}

void GlutWrapper::UpdateParam()
{

}

GlutWrapper::GlutWrapper(const char* title, int width, int height, float lightAngle)
    :_width(width), _height(height), _lightAngle(lightAngle)
{
    glutInitWindowSize(400,400);
    glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutCreateWindow(title);
    glutDisplayFunc(_display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(_reshape);

    if (glewInit() != GLEW_OK || !GLEW_VERSION_1_1)
    {
        std::cout<<"failed to initialize GLEW, OpenGL 1.1 required.\n"<< title;
        exit(1);
    }

    requestSynchronizedSwapBuffers();
    glClearColor(0.1, 0.3, 0.6, 0.0);  /* Blue background */
    glEnable(GL_DEPTH_TEST);
}