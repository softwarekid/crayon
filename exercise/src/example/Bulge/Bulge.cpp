#include "Bulge.h"
#include <CG/cgGL.h>
#include "BulgeVsParam.h"
#include "BulgeFsParam.h"
#include <CgLog.h>

void Bulge::_InitMaterial()
{
    redMaterial.kd = Vector3f(0.8, 0.1, 0.1);
    redMaterial.shininess = 35;
    greenMaterial.kd = Vector3f(0.1, 0.7, 0.1);
    greenMaterial.shininess = 35;
}

void Bulge::_InitConstShaderParams()
{
    _vertParams->SetLightColor(Vector3f(0.95f, 0.95f, 0.95f));
    _vertParams->SetScaleFactor(0.3);
    _vertParams->SetFrequency(2.4);
}

void Bulge::_SetMaterial(Material m)
{
    _vertParams->SetKd(m.kd);
    _vertParams->SetShininess(m.shininess);
}

void Bulge::_Idle()
{
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
    translation = Vector3f(2.2, 1, 0.2);
    rotation = Vector4f(-70, 1, 1, 1);
    _Draw(rotation, translation, eyePosition, lightPosition, redMaterial, _sphereDrawer);

    translation = Vector3f(-2, -1.5, 0);
    rotation = Vector4f(-55, 1, 0, 0);
    _Draw(rotation, translation, eyePosition, lightPosition, greenMaterial, _torusDrawer);

    _vertShader->DisableProfile();
    _fragShader->DisableProfile();
    glutSwapBuffers();
}

void Bulge::_InitVertShader()
{
    auto profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
    std::string fileName(R"(src\example\Bulge\bulge_V.cg)");
    std::string entry("main_v");
    _vertShader = new CgShader(_context, profileVertex, fileName, entry);
    _vertParams = new BulgeVsParam(*_vertShader);
    _vertParams->ExtractParams();

    string lightVetexFileName(R"(src\example\Bulge\LightVsParam.cg)");
    _lightVertexShader = new CgShader(_context, profileVertex, lightVetexFileName, entry);
    _lightVsParam = new BulgeLightVsParam(*_lightVertexShader);
    _lightVsParam->ExtractParams();
    cgGLSetOptimalOptions(profileVertex);
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