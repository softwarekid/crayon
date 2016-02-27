#include "GlutWrapper.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include <iostream>
#include "CgShader.h"
#include <CG/cgGL.h>

std::map<int, GlutWrapper*> GlutWrapper::_windows;

void GlutWrapper::__Keyboard(unsigned char c, int x, int y)
{
    static bool animating = false;
    if(c == ' ')
    {
        animating = !animating;
        if(animating)
            glutIdleFunc(__Idle);
        else
            glutIdleFunc(nullptr);
    }
    else
    {
        __CurrentWindow()->_Keyboard(c, x, y);
    }
}

void GlutWrapper::__Idle()
{
    __CurrentWindow()->_Idle();
}

void GlutWrapper::__Reshape(int width, int height)
{
    __CurrentWindow()->_Reshape(width, height);
}

void GlutWrapper::__Display()
{
    __CurrentWindow()->_Display();
}

void GlutWrapper::__Menu()
{
    __CurrentWindow()->_Menu();
}

GlutWrapper* GlutWrapper::__CurrentWindow()
{
    return _windows[glutGetWindow()];
}

void GlutWrapper::_Keyboard(int c, int x, int y)
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
        _Exit();
        break;
    }
}

void GlutWrapper::_Reshape(int width, int height)
{
    float aspectRatio = (float)width / (float) height;
    float fov = 40.0f;
    _transform.SetProjection(fov,aspectRatio,1.0, 20.0);
    glViewport(0, 0, width, height);
}

void GlutWrapper::_Exit()
{
    cgDestroyContext(_context);
    exit(0);
}

void GlutWrapper::_RequestSynchronizedSwapBuffers()
{
#ifdef _WIN32
    if(wglSwapIntervalEXT)
    {
        wglSwapIntervalEXT(1);
    }
#endif
}

void GlutWrapper::SetTranslate(float x, float y, float z)
{
    _transform.SetTranslate(x,y,z);
}

void GlutWrapper::SetRotation(float angle, float axis_x, float axis_y, float axis_z)
{
    _transform.SetArbitraryRotation(angle, axis_x, axis_y, axis_z);
}

void GlutWrapper::SetCamera(Camera camera)
{
    _transform.SetCamera(camera);
}

void GlutWrapper::SetMesh(Mesh mesh)
{
    _mesh = mesh;
}

void GlutWrapper::StartRendering()
{
    _InitVertShader();
    _InitFragShader();
    _InitShaderParams();
    glutMainLoop();
}

GlutWrapper::GlutWrapper(const char* title, int width, int height)
    :_width(width), _height(height)
{
    glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(width, height);
    _windowID = glutCreateWindow(title);
    _windows[_windowID] = this;

    glutDisplayFunc(__Display);
    glutKeyboardFunc(__Keyboard);
    glutReshapeFunc(__Reshape);

    if (glewInit() != GLEW_OK || !GLEW_VERSION_1_1)
    {
        std::cout<<"failed to initialize GLEW, OpenGL 1.1 required.\n"<< title;
        exit(1);
    }

    _RequestSynchronizedSwapBuffers();
    glClearColor(0.1, 0.3, 0.6, 0.0);  /* Blue background */
}

GlutWrapper::~GlutWrapper()
{
    glutDestroyWindow(_windowID);
    delete _vertShader;
    delete _fragShader;
}