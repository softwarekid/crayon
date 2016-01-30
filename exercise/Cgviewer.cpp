#include "CgViewer.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "Constants.h"
using namespace std;


CgViewer::CgViewer(const char* title, int width, int height, float lightAngle):
         GlutWrapper(title, width, height)
{
    _lightAngle = lightAngle;
    glClearColor(0.1, 0.3, 0.6, 0.0);  /* Blue background */
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
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
        _Exit();
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

void CgViewer::_Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _verShader.LoadProgram();
    _fragShader.LoadProgram();
    cgGLBindProgram(programVertex);
    Log("binding vertex program");

    cgGLEnableProfile(profileVertex);
    Log("enabling vertex profile");

    cgGLBindProgram(programFragment);
    Log("binding fragment program");

    cgGLEnableProfile(profileFragment);
    Log("enabling fragment profile");

    setBrassMaterial();
    transform.SetTranslate(2, 0, 0);
    transform.SetArbitraryRotation(20, 1, 1, 1);
    Matrix4f modelMatrix;
    transform.GetModelMatrix(modelMatrix);
    Matrix4f invModelMatrix = modelMatrix.Invert();
    Vector4f objSpaceEyePosition = invModelMatrix.Mul(eyePosition);
    Vector4f objSpaceLightPosition = invModelMatrix.Mul(lightPosition);
    Matrix4f modelViewProjMatix;
    transform.GetMVPMatrix(modelViewProjMatix);
    CgSetParam(paramVertexmodelViewProj, modelViewProjMatix);

    //CgSetParam(paramFragmentEyePosition, objSpaceEyePosition);
    CgSetParam(paramFragmentLightPosition, objSpaceLightPosition);

    CgSetParam(paramVertexLightPosition, objSpaceLightPosition);
    CgSetParam(paramVertexEyePosition, objSpaceEyePosition);

    cgUpdateProgramParameters(programVertex);
    cgUpdateProgramParameters(programFragment);
    glutSolidSphere(2.0, 10, 10);

    cgGLDisableProfile(profileVertex);
    Log("disabling vertex profile");

    cgGLDisableProfile(profileFragment);
    Log("disabling fragment profile");
    glutSwapBuffers();
}