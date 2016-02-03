#include "GlutWrapper.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include <iostream>
#include "CgShader.h"

std::map<int, GlutWrapper*> _windows;

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
}

GlutWrapper::~GlutWrapper()
{
    glutDestroyWindow(_windowID);
    delete _vertShader;
    delete _fragShader;
}