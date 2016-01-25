#include "GlutWrapper.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include <iostream>

std::map<int, GlutWrapper*> _windows;

void GlutWrapper::__Keyboard(unsigned char c, int x, int y)
{
    __CurrentWindow()->_Keyboard(c, x, y);
}

void GlutWrapper::__Idle()
{
    __CurrentWindow()->_Idle();
}

void GlutWrapper::__Display()
{
    __CurrentWindow()->_Display();
}

GlutWrapper* GlutWrapper::__CurrentWindow()
{
    return _windows[glutGetWindow()];
}

void GlutWrapper::Init()
{
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

void GlutWrapper::UpdateParam()
{

}

GlutWrapper::GlutWrapper(const char* title, int width, int height, float lightAngle)
    :_width(width), _height(height), _lightAngle(lightAngle)
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
    Init();
}

GlutWrapper::~GlutWrapper()
{
    glutDestroyWindow(_windowID);
}