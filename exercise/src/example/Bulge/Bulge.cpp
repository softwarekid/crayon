#include "Bulge.h"
#include <CG/cgGL.h>
#include "BulgeVsParam.h"
#include "BulgeFsParam.h"
#include <CgLog.h>
#include "Constants.h"
#include <GL/glut.h>

void Bulge::_InitMaterial()
{
    redMaterial.kd = Vector3f(0.8, 0.1, 0.1);
    redMaterial.shininess = 35;
    greenMaterial.kd = Vector3f(0.1, 0.7, 0.1);
    greenMaterial.shininess = 35;
}

void Bulge::_InitConstShaderParams()
{
}

void Bulge::_SetMaterial(Material m)
{
}

void Bulge::_Draw(const Vector4f& rotation, const Vector3f& translate, const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw)
{
    _SetMaterial(m);
    _transform.SetArbitraryRotation(rotation[1], rotation[2], rotation[3], rotation[4]);
    _transform.SetTranslate(translate.x, translate.y, translate.z);
    Matrix4f modelMatrix;
    _transform.GetModelMatrix(modelMatrix);
    //TODO can I use rvalue-reference here?
    Matrix4f invModelMatrix = modelMatrix.Invert();

    Vector3f objSpaceEyePosition = _MatVecMulReduced(invModelMatrix, eyePos);
    _vertParams->SetEyePosition(objSpaceEyePosition);
    Vector3f objSpaceLightPosition = _MatVecMulReduced(invModelMatrix, lightPosition);
    _vertParams->SetLightPos(objSpaceLightPosition);
    Matrix4f modelViewProjMatix;
    _transform.GetMVPMatrix(modelViewProjMatix);
    _vertParams->SetMVPMatrix(modelViewProjMatix);
    // deferred params are updated, aka, perform a draw call
    _vertShader->UpdateParams();
    _fragShader->UpdateParams();
    draw();
}

void Bulge::_Idle()
{
    static float lightVelocity = 0.008;
    static float timeFlow = 0.01;

    /* Repeat rotating light around front 180 degrees. */
    if (_lightAngle > Constants::Math::PI / 2)
    {
        _lightAngle = Constants::Math::PI / 2;
        lightVelocity = -lightVelocity;
    }
    else if (_lightAngle < -Constants::Math::PI / 2)
    {
        _lightAngle = -Constants::Math::PI / 2;
        lightVelocity = -lightVelocity;
    }
    _lightAngle += lightVelocity;  /* Add a small angle (in radians). */

    /* Repeatedly advance and rewind time. */
    if (_time > 10)
    {
        _time = 10;
        timeFlow = -timeFlow;
    }
    else if (_time < 0)
    {
        _time = 0;
        timeFlow = -timeFlow;
    }
    _time += timeFlow;  /* Add time delta. */
    glutPostRedisplay();

}

void Bulge::_Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Vector3f eyePosition(0, 0, 13);
    const Vector3f eyeCenter(0, 0, 0);
    const Vector3f eyeUp(0, 1, 0);
    const Vector3f lightPosition(5 * sin(_lightAngle), 1.5, 5 * cos(_lightAngle));

    _vertShader->EnableProfile();
    _fragShader->EnableProfile();
    _vertShader->BindProgram();
    _fragShader->BindProgram();

    _InitConstShaderParams();
    _vertParams->SetTime(_time);
    Camera camera(eyePosition, eyeCenter, eyeUp);
    _transform.SetCamera(camera);
    Vector3f translation;
    Vector4f rotation;
    translation = Vector3f(2.2, -1, 0.2);
    rotation = Vector4f(-70, 1, 1, 1);
    _Draw(rotation, translation, eyePosition, lightPosition, redMaterial, [](){glutSolidSphere(1, 40, 40); });

    translation = Vector3f(-2, 1.5, 0);
    rotation = Vector4f(-55, 1, 0, 0);
    _Draw(rotation, translation, eyePosition, lightPosition, greenMaterial, [](){glutSolidTorus(0.15, 1.7, 40, 40); });

    _vertShader->DisableProfile();
    _fragShader->DisableProfile();
    glutSwapBuffers();
}

void Bulge::_InitVertShader()
{
    //auto profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
    //std::string fileName(R"(src\example\Bulge\bulge_V.cg)");
    //std::string entry("main_v");
    //_vertShader = new CgShader(_context, profileVertex, fileName, entry);
    //_vertParams = new BulgeVsParam(*_vertShader);
    //_vertParams->ExtractParams();

    //string lightVetexFileName(R"(src\example\Bulge\LightVsParam.cg)");
    //_lightVertexShader = new CgShader(_context, profileVertex, lightVetexFileName, entry);
    //_lightVsParam = new BulgeLightVsParam(*_lightVertexShader);
    //_lightVsParam->ExtractParams();
    //cgGLSetOptimalOptions(profileVertex);
}

void Bulge::_InitFragShader()
{
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    std::string fileName(R"(src\example\Bulge\bulge_F.cg)");
    std::string entry("main_f");
    _fragShader = new CgShader(_context, profileFrag, fileName, entry);
    _fragParams = new BulgeFsParam(*_fragShader);
    _fragParams->ExtractParams();

    string lightFragFileName(R"(src\example\Bulge\LightFsParam.cg)");
    _lightFragShader = new CgShader(_context, profileFrag, lightFragFileName, entry);
    _lightFsParam = new BulgeLightFsParam(*_lightFragShader);
    cgGLSetOptimalOptions(profileFrag);
}

Bulge::Bulge(const char* title, int width, int height) : GlutWrapper(title, width, height)
{
    glEnable(GL_DEPTH_TEST);
    //glClearColor(0.1, 0.1, 0.1, 0);  /* Gray background. */
    _context = cgCreateContext();
    CgLog::Log("create content", _context);
    cgGLSetDebugMode(CG_TRUE);
    cgSetParameterSettingMode(_context,CG_DEFERRED_PARAMETER_SETTING);
    CgLog::Log("selecting vertex profile", _context);

    _lightAngle = -0.4f;
    _time = 0;
    _InitMaterial();
}