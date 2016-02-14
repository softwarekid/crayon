#include "CgViewer.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "Constants.h"
#include <CG/cgGL.h>
#include "CgLog.h"
#include "VertShaderParam.h"
#include "FragShaderParam.h"
using namespace std;


void CgViewer::InitVertShader()
{
    auto profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
    string fileName("");
    string entry("");
    _vertShader = new CgShader(_context, profileVertex, fileName, entry);
    _vertParams = new VertShaderParam(*_vertShader);
    _vertParams->Init();
    cgGLSetOptimalOptions(profileVertex);
}

void CgViewer::InitFragShader()
{
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    string fileName("");
    string entry("");
    _fragShader = new CgShader(_context, profileFrag, fileName, entry);
    _fragParams = new FragShaderParam(*_fragShader);
    _fragParams->Init();
    cgGLSetOptimalOptions(profileFrag);
}

void CgViewer::StartRendering()
{
    // At the beginning I plan to initialize the two shaders in the ctor, but as 
    // virtual functions they are not allowed to appear in the ctor, so I add 
    // this "indirect layer" to do the start.
    InitVertShader();
    InitFragShader();
    glutMainLoop();
}

CgViewer::CgViewer(const char* title, int width, int height, float lightAngle):
         GlutWrapper(title, width, height)
{
    _lightAngle = lightAngle;
    glClearColor(0.1, 0.3, 0.6, 0.0);  /* Blue background */
    glEnable(GL_DEPTH_TEST);
    _context = cgCreateContext();
    CgLog::Log("create content", _context);
    cgGLSetDebugMode(CG_TRUE);
    cgSetParameterSettingMode(_context,CG_DEFERRED_PARAMETER_SETTING);
    CgLog::Log("selecting vertex profile", _context);
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
    _vertShader->BindProgram();
    _vertShader->EnableProfile();
    _fragShader->BindProgram();
    _fragShader->EnableProfile();

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

void CgViewer::SetMaterial()
{
    // brass 
    _fragParams->SetKaCoef(Vector3f(0.33, 0.22, 0.03));
    _fragParams->SetKeCoef(Vector3f(0, 0, 0));
    _fragParams->SetKdCoef(Vector3f(0.78, 0.57, 0.11));
    _fragParams->SetKsCoef(Vector3f(0.99, 0.91, 0.81));
    _fragParams->SetShinessCoef(27.8);
}