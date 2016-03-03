#include <assert.h>
#include "TwoLightsWithStruct.h"
#include <CG/cgGL.h>
#include <vector>
#include <GL/glut.h>
#include <CgLog.h>
#include <Constants.h>
using namespace std;

void TwoLightsWithStruct::_SetBrassMaterial()
{
}

void TwoLightsWithStruct::_SetRedPlasticMaterial()
{
}

void TwoLightsWithStruct::_SetEmissiveOnly(int lightIndex)
{
    assert(lightIndex >= 0 && lightIndex <= 1);
}

void TwoLightsWithStruct::_InitMaterial()
{
    // brass material
    brassMaterial.ke = { 0.0f, 0.0f, 0.0f };
    brassMaterial.ka = { 0.33f, 0.22f, 0.03f };
    brassMaterial.kd = { 0.78f, 0.57f, 0.11f };
    brassMaterial.ks = { 0.99f, 0.91f, 0.81f };
    brassMaterial.shininess = 27.8;

    // red plastic 
    redPlasticMaterial.ke = { 0.0f, 0.0f, 0.0f };
    redPlasticMaterial.ka = { 0.0f, 0.0f, 0.0f };
    redPlasticMaterial.kd = { 0.5f, 0.0f, 0.0f };
    redPlasticMaterial.ks = { 0.7f, 0.6f, 0.6f };
    redPlasticMaterial.shininess = 32.0f;

    // only emissive
    for (int i = 0; i < 2; i++)
    {
        emissiveMaterial[i].ke = Vector3f( _lightColors[i].x, _lightColors[i].y, _lightColors[i].z );
        emissiveMaterial[i].ka = { 0.0f, 0.0f, 0.0f };
        emissiveMaterial[i].kd = { 0.0f, 0.0f, 0.0f };
        emissiveMaterial[i].ks = { 0.0f, 0.0f, 0.0f };
        emissiveMaterial->shininess = 0.0f;
    }
}

void TwoLightsWithStruct::_SetMaterial(const Material& m)
{
    _vertParams->SetMaterialKe(m.ke);
    _vertParams->SetMaterialKa(m.ka);
    _vertParams->SetMaterialKd(m.kd);
    _vertParams->SetMaterialKs(m.ks);
    _vertParams->SetMaterialShininess(m.shininess);
}

void TwoLightsWithStruct::_Draw(const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const vector<Vector3f>& lightPositions, const Material& m, RenderObject obj )
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
    for (int i = 0; i < lightPositions.size(); i++)
    {
        Vector3f objSpaceLightPosition = _MatVecMulReduced(invModelMatrix, lightPositions[i]);
        _vertParams->SetLightPos(i, objSpaceLightPosition);
    }
    Matrix4f modelViewProjMatix;
    _transform.GetMVPMatrix(modelViewProjMatix);
    _vertParams->SetMVPMatrix(modelViewProjMatix);
    // deferred params are updated, aka, perform a draw call
    _vertShader->UpdateParams();
    switch (obj)
    {
    case RenderObject::Sphere:
        glutSolidSphere(2.0, 40, 40);
        break;
    case RenderObject::Cone:
        glutSolidCone(1.5, 3.5, 30, 30);
        break;
    case RenderObject::SmallSphere:
        glutSolidSphere(0.2, 12, 12);
    }
}

void TwoLightsWithStruct::_Idle()
{
    _lightAngles[0] += 0.008;  /* Add a small angle (in radians). */
    if (_lightAngles[0] > 2 * Constants::Math::PI)
    {
        _lightAngles[0] -= 2 * Constants::Math::PI;
    }
    _lightAngles[1] -= 0.005;  /* Add a small angle (in radians). */
    if (_lightAngles[1] < 2 * Constants::Math::PI) 
    {
        _lightAngles[1] += 2 * Constants::Math::PI;
    }
    glutPostRedisplay();
}

void TwoLightsWithStruct::_Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Vector3f eyePosition(0, 0, 13);
    const Vector3f eyeCenter(0, 0, 0);
    const Vector3f eyeUp(0, 1, 0);
    const vector<Vector3f> lightPositions{Vector3f(5 * sin(_lightAngles[0]), 1.5, 5 * cos(_lightAngles[0])),
                                          Vector3f(5 * sin(_lightAngles[1]), 0.25, 5 * cos(_lightAngles[1]))};
    _vertShader->BindProgram();
    _vertShader->EnableProfile();
    _fragShader->BindProgram();
    _fragShader->EnableProfile();

    _InitLightColor();
    Camera camera(eyePosition, eyeCenter, eyeUp);
    _transform.SetCamera(camera);
    Vector3f translation;
    Vector4f rotation;

    translation = Vector3f(2, 0, 0);
    rotation = Vector4f(-70, 1, 1, 1);
    _Draw(rotation, translation, eyePosition, lightPositions, brassMaterial, RenderObject::Sphere);

    translation = Vector3f(-2.0f, -1.5f, 0);
    rotation = Vector4f(-90, 1, 0, 0);
    _Draw(rotation, translation, eyePosition, lightPositions, redPlasticMaterial, RenderObject::Cone);

    for (int i = 0; i < 2; i++)
    {
        rotation = Vector4f(0, 1, 0, 0);
        _Draw(rotation, lightPositions[i], eyePosition, lightPositions, emissiveMaterial[i], RenderObject::SmallSphere);
    }

    _vertShader->DisableProfile();
    _fragShader->DisableProfile();
    glutSwapBuffers();
}

void TwoLightsWithStruct::_InitVertShader()
{
    auto profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
    string fileName(R"(src\example\TwoLightsWithStruct\TwoLightsWithStruct_V.cg)");
    string entry("main_v");
    _vertShader = new CgShader(_context, profileVertex, fileName, entry);
    _vertParams = new TwoLightsWithStructVsParam(*_vertShader);
    _vertParams->ExtractParams();
    cgGLSetOptimalOptions(profileVertex);
}

void TwoLightsWithStruct::_InitFragShader()
{
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    string fileName(R"(src\example\TwoLightsWithStruct\TwoLightsWithStruct_F.cg)");
    string entry("main_f");
    _fragShader = new CgShader(_context, profileFrag, fileName, entry);
    _fragParams = new TwoLightsWithStructFsParam(*_fragShader);
    _fragParams->ExtractParams();
    cgGLSetOptimalOptions(profileFrag);
}

void TwoLightsWithStruct::_InitLightColor()
{
    for (int i = 0; i < 2; i++)
    {
        _vertParams->SetLightColor(i, _lightColors[i]);
    }
    _vertParams->SetGlobalAmbient(Vector3f(0.1, 0.1, 0.1));
}

TwoLightsWithStruct::TwoLightsWithStruct(const char* title, int width, int height) : GlutWrapper(title, width, height)
{
    glEnable(GL_DEPTH_TEST);
    _lightAngles[0] = -0.4;
    _lightAngles[1] = -0.1;
    _lightColors[0] = Vector3f(0.95, 0.95, 0.95);
    _lightColors[1] = Vector3f(0.5, 0.5, 0.2);
    _context = cgCreateContext();
    CgLog::Log("create content", _context);
    cgGLSetDebugMode(CG_TRUE);
    cgSetParameterSettingMode(_context,CG_DEFERRED_PARAMETER_SETTING);
    CgLog::Log("selecting vertex profile", _context);
    _InitMaterial();
}