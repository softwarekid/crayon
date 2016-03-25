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

    _sceneProgram->BindShader();
    _sceneProgram->EnableProfile();
    _sceneProgram->InitConstShaderParams();
    _sceneProgram->SetTime(_time);
    Camera camera(eyePosition, eyeCenter, eyeUp);
    Vector3f translation;
    Vector4f rotation;
    translation = Vector3f(2.2, -1, 0.2);
    rotation = Vector4f(-70, 1, 1, 1);
    _sceneProgram->Draw(camera, rotation, translation, eyePosition, lightPosition, redMaterial, [](){glutSolidSphere(1, 40, 40); });

    translation = Vector3f(-2, 1.5, 0);
    rotation = Vector4f(-55, 1, 0, 0);
    _sceneProgram->Draw(camera, rotation, translation, eyePosition, lightPosition, greenMaterial, [](){glutSolidTorus(0.15, 1.7, 40, 40);});

    translation = lightPosition;
    rotation = Vector4f(0 ,1, 0, 0);
    _lightPrgoram->BindShader();
    _lightPrgoram->Draw(camera, rotation, translation, eyePosition, lightPosition, emptyMaterial, [](){glutSolidSphere(0.1, 12, 12);});
    _lightPrgoram->DisableProfile();
    _sceneProgram->DisableProfile();
    glutSwapBuffers();
}

Bulge::Bulge(const char* title, int width, int height) : GlutWrapper(title, width, height)
{
    glEnable(GL_DEPTH_TEST);
    //glClearColor(0.1, 0.1, 0.1, 0);  /* Gray background. */
    _context = cgCreateContext();
    CgLog::Log("create content", _context);
    cgGLSetDebugMode(CG_TRUE);
    cgSetParameterSettingMode(_context,CG_DEFERRED_PARAMETER_SETTING);

    
    auto profileVert = cgGLGetLatestProfile(CG_GL_VERTEX);
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    cgGLSetOptimalOptions(profileVert);
    cgGLSetOptimalOptions(profileFrag);
    CgLog::Log("selecting vertex profile", _context);

    _sceneProgram = new SceneDrawCall(_context, profileVert, profileFrag, sceneVertShaderName, vertEntry, sceneFragShaderName, fragEntry);
    _sceneProgram->SetProjection(40, (float)width / (float)height, 0.1, 100);

    _lightPrgoram = new BulgeLightDrawCall(_context, profileVert, profileFrag, lightVertShaderName , vertEntry, lightFragShaderName, fragEntry);
    _lightPrgoram->SetProjection(40, (float)width / (float)height, 0.1, 100);

    _lightAngle = -0.4f;
    _time = 0;
    _InitMaterial();
}

Bulge::~Bulge()
{
    delete _sceneProgram;
    delete _lightPrgoram;
}