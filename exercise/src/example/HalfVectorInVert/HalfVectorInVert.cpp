#include "HalfVectorInVert.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "Constants.h"
#include <CG/cgGL.h>
#include "CgLog.h"
#include "HalfVectorVsParam.h"
#include "HalfVectorFsParam.h"
using namespace std;


void HalfVectorInVert::_InitVertShader()
{
    auto profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
    string fileName(R"(src\example\HalfVectorInVert\HalfVectorInVert_V.cg)");
    string entry("main_v");
    _vertShader = new CgShader(_context, profileVertex, fileName, entry);
    _vertParams = new HalfVectorVsParam(*_vertShader);
    _vertParams->ExtractParams();
    cgGLSetOptimalOptions(profileVertex);
}

void HalfVectorInVert::_InitFragShader()
{
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    string fileName(R"(src\example\HalfVectorInVert\HalfVectorInVert_F.cg)");
    string entry("main_f");
    _fragShader = new CgShader(_context, profileFrag, fileName, entry);
    _fragParams = new HalfVectorFsParam(*_fragShader);
    _fragParams->ExtractParams();
    cgGLSetOptimalOptions(profileFrag);
}

HalfVectorInVert::HalfVectorInVert(const char* title, int width, int height, float lightAngle):
         GlutWrapper(title, width, height)
{
    _lightAngle = lightAngle;
    glEnable(GL_DEPTH_TEST);
    _context = cgCreateContext();
    CgLog::Log("create content", _context);
    cgGLSetDebugMode(CG_TRUE);
    cgSetParameterSettingMode(_context,CG_DEFERRED_PARAMETER_SETTING);
    CgLog::Log("selecting vertex profile", _context);
}

void HalfVectorInVert::_Idle()
{
    _lightAngle += 0.008;
    if(_lightAngle > 2 * Constants::Math::PI)
    {
        _lightAngle -= 2 * Constants::Math::PI;
    }
    glutPostRedisplay();
}

void HalfVectorInVert::_Reshape(int width, int height)
{
    float aspectRatio = (float)width / (float) height;
    float fov = 40.0f;
    _transform.SetProjection(fov,aspectRatio,1.0, 20.0);
    glViewport(0, 0, width, height);
}

void HalfVectorInVert::_Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _InitShaderParams();

    const Vector3f eyePosition(0, 0, 13);
    const Vector3f eyeCenter(0,0,0);
    const Vector3f eyeUp(0,1,0);
    const Vector3f lightPosition(5 * sin(_lightAngle), 1.5, 5 * cos(_lightAngle));
    _vertShader->BindProgram();
    _vertShader->EnableProfile();
    _fragShader->BindProgram();
    _fragShader->EnableProfile();
    Camera camera(eyePosition, eyeCenter, eyeUp);
    _transform.SetCamera(camera);
    _transform.SetTranslate(2, 0, 0);
    _transform.SetArbitraryRotation(20, 1, 1, 1);
    Matrix4f modelMatrix;
    _transform.GetModelMatrix(modelMatrix);
    Matrix4f invModelMatrix = modelMatrix.Invert();
    Vector3f objSpaceEyePosition = _MatVecMulReduced(invModelMatrix, eyePosition);
    Vector3f objSpaceLightPosition = _MatVecMulReduced(invModelMatrix, lightPosition);
    _fragParams->SetLightPosition(objSpaceLightPosition);
    _vertParams->SetLightPosition(objSpaceLightPosition);
    _vertParams->SetEyePostion(objSpaceEyePosition);
    Matrix4f modelViewProjMatix;
    _transform.GetMVPMatrix(modelViewProjMatix);
    _vertParams->SetMVPMatrix(modelViewProjMatix);

    _vertShader->UpdateParams();
    _fragShader->UpdateParams();
    _mesh.Render();

    _vertShader->DisableProfile();
    _fragShader->DisableProfile();
    glutSwapBuffers();
}

void HalfVectorInVert::_InitShaderParams()
{
    // brass material
    _fragParams->SetKaCoef(Vector3f(0.33, 0.22, 0.03));
    _fragParams->SetKeCoef(Vector3f(0, 0, 0));
    _fragParams->SetKdCoef(Vector3f(0.78, 0.57, 0.11));
    _fragParams->SetKsCoef(Vector3f(0.99, 0.91, 0.81));
    _fragParams->SetShinessCoef(27.8);

    // light color
    _fragParams->SetLightColor(Vector3f(0.95f, 0.95f, 0.95f));
}
