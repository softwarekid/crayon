#include "AttenuateLighting.h"
#include "AttenuateLightingVsParam.h"
#include "AttenuateLightingFsParam.h"
#include <CG/cgGL.h>
#include <GL/glut.h>
#include <CgLog.h>
#include <Constants.h>
using namespace std;
void AttenateLighting::_Draw(const Vector4f& rotation, const Vector3f& translate, const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, RenderObject obj)
{
    _SetMaterial(m);
    _transform.SetArbitraryRotation(rotation[1], rotation[2], rotation[3], rotation[4]);
    _transform.SetTranslate(translate.x, translate.y, translate.z);
    Matrix4f modelMatrix;
    _transform.GetModelMatrix(modelMatrix);
    //TODO can I use rvalue-reference here?
    Matrix4f invModelMatrix = modelMatrix.Invert();

    Vector3f objSpaceEyePosition = _MatVecMulReduced(invModelMatrix, eyePos);
    _fragParams->SetEyePosition(objSpaceEyePosition);
    Vector3f objSpaceLightPosition = _MatVecMulReduced(invModelMatrix, lightPosition);
    _fragParams->SetLightPos(objSpaceLightPosition);
    Matrix4f modelViewProjMatix;
    _transform.GetMVPMatrix(modelViewProjMatix);
    _vertParams->SetMVPMatrix(modelViewProjMatix);
    // deferred params are updated, aka, perform a draw call
    _vertShader->UpdateParams();
    _fragShader->UpdateParams();
    _RenderMesh(obj);
}

void AttenateLighting::_RenderMesh(RenderObject mesh)
{
    switch (mesh)
    {
    case RenderObject::Sphere:
        glutSolidSphere(2.0, 40, 40);
        break;
    case RenderObject::Cone:
        glutSolidCone(1.5, 3.5, 30, 30);
        break;
    case RenderObject::SmallSphere:
        glutSolidSphere(0.2, 12, 12);
        break;
    case RenderObject::Box:
        glBegin(GL_QUADS);
        glNormal3f(0, 1, 0);
        glVertex3f(12, -2, -12);
        glVertex3f(-12, -2, -12);
        glVertex3f(-12, -2, 12);
        glVertex3f(12, -2, 12);

        glNormal3f(0, 0, 1);
        glVertex3f(-12, -2, -12);
        glVertex3f(12, -2, -12);
        glVertex3f(12, 10, -12);
        glVertex3f(-12, 10, -12);

        glNormal3f(0, -1, 0);
        glVertex3f(-12, 10, -12);
        glVertex3f(12, 10, -12);
        glVertex3f(12, 10, 12);
        glVertex3f(-12, 10, 12);

        glNormal3f(1, 0, 0);
        glVertex3f(-12, -2, 12);
        glVertex3f(-12, -2, -12);
        glVertex3f(-12, 10, -12);
        glVertex3f(-12, 10, 12);

        glNormal3f(-1, 0, 0);
        glVertex3f(12, -2, -12);
        glVertex3f(12, -2, 12);
        glVertex3f(12, 10, 12);
        glVertex3f(12, 10, -12);
        glEnd();
        break;
    }
}

void AttenateLighting::_SetMaterial(const Material& m)
{
    _fragParams->SetMaterialKe(m.ke);
    _fragParams->SetMaterialKa(m.ka);
    _fragParams->SetMaterialKd(m.kd);
    _fragParams->SetMaterialKs(m.ks);
    _fragParams->SetMaterialShininess(m.shininess);
}

void AttenateLighting::_SetLightIntrinsicParam()
{
    _fragParams->SetLightColor(_lightColor);
    _fragParams->SetGlobalAmbient(Vector3f(0.5,0.5,0.5));
    _fragParams->SetLightAttenKc(_lightKc);
    _fragParams->SetLightAttenKl(_lightKl);
    _fragParams->SetLightAttenKq(_lightKq);
}

void AttenateLighting::_InitMaterial()
{
    // brass material
    _brassMaterial.ke = { 0.0f, 0.0f, 0.0f };
    _brassMaterial.ka = { 0.33f, 0.22f, 0.03f };
    _brassMaterial.kd = { 0.78f, 0.57f, 0.11f };
    _brassMaterial.ks = { 0.99f, 0.91f, 0.81f };
    _brassMaterial.shininess = 27.8;

    // red plastic 
    _redPlasticMaterial.ke = { 0.0f, 0.0f, 0.0f };
    _redPlasticMaterial.ka = { 0.0f, 0.0f, 0.0f };
    _redPlasticMaterial.kd = { 0.5f, 0.0f, 0.0f };
    _redPlasticMaterial.ks = { 0.7f, 0.6f, 0.6f };
    _redPlasticMaterial.shininess = 32.0f;

    // green emerald
    _greenEmeraldMaterial.ke = Vector3f(0.0f, 0.0f, 0.0f);
    _greenEmeraldMaterial.ka = Vector3f(0.0215, 0.1745, 0.0215);
    _greenEmeraldMaterial.kd = Vector3f(0.07568, 0.61424, 0.07568);
    _greenEmeraldMaterial.ks = Vector3f(0.633, 0.727811, 0.633);
    _greenEmeraldMaterial.shininess = 76.8f;

    // only emissive
    _emissiveMaterial.ke = _lightColor;
    _emissiveMaterial.ka = { 0.0f, 0.0f, 0.0f };
    _emissiveMaterial.kd = { 0.0f, 0.0f, 0.0f };
    _emissiveMaterial.ks = { 0.0f, 0.0f, 0.0f };
    _emissiveMaterial.shininess = 0.0f;
}

void AttenateLighting::_Idle()
{
    _lightAngle += 0.008;  /* Add a small angle (in radians). */
    if (_lightAngle > 2 * Constants::Math::PI)
    {
        _lightAngle -= 2 * Constants::Math::PI;
    }
    glutPostRedisplay();
}

void AttenateLighting::_Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Vector3f eyePosition(0, 0, 13);
    const Vector3f eyeCenter(0, 0, 0);
    const Vector3f eyeUp(0, 1, 0);
    const Vector3f lightPosition = Vector3f(5 * sin(_lightAngle), 1.5, 5 * cos(_lightAngle));
    _vertShader->BindProgram();
    _vertShader->EnableProfile();
    _fragShader->BindProgram();
    _fragShader->EnableProfile();

    Camera camera(eyePosition, eyeCenter, eyeUp);
    _transform.SetCamera(camera);
    _SetLightIntrinsicParam();

    Vector3f translation;
    Vector4f rotation;

    translation = Vector3f(2, 0, 0);
    rotation = Vector4f(0, 1, 1, 1);
    _Draw(rotation, translation, eyePosition, lightPosition, _brassMaterial, RenderObject::Sphere);

    translation = Vector3f(-2, -1.5, 0);
    rotation = Vector4f(-90, 1, 0, 0);
    _Draw(rotation, translation, eyePosition, lightPosition, _redPlasticMaterial, RenderObject::Cone);


    translation = Vector3f(0, 0, 0);
    rotation = Vector4f(0, 1, 0, 0);
    _Draw(rotation, translation, eyePosition, lightPosition, _greenEmeraldMaterial, RenderObject::Box);

    translation = lightPosition;
    rotation = Vector4f(0, 1, 0, 0);
    _Draw(rotation, translation, eyePosition, lightPosition, _emissiveMaterial, RenderObject::SmallSphere);

    _vertShader->DisableProfile();
    _fragShader->DisableProfile();
    glutSwapBuffers();
}

void AttenateLighting::_InitVertShader()
{
    auto profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
    string fileName(R"(src\example\AttenuateLight\attenuateLight_V.cg)");
    string entry("main_v");
    _vertShader = new CgShader(_context, profileVertex, fileName, entry);
    _vertParams = new AttenuateLightingVsParam(*_vertShader);
    _vertParams->ExtractParams();
    cgGLSetOptimalOptions(profileVertex);
}

void AttenateLighting::_InitFragShader()
{
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    string fileName(R"(src\example\AttenuateLight\attenuateLight_F.cg)");
    string entry("main_f");
    _fragShader = new CgShader(_context, profileFrag, fileName, entry);
    _fragParams = new AttenuateLightingFsParam(*_fragShader);
    _fragParams->ExtractParams();
    cgGLSetOptimalOptions(profileFrag);
}

AttenateLighting::AttenateLighting(const char* title, int width, int height) :GlutWrapper(title, width, height)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1, 0.1, 0.1, 0);  /* Gray background. */
    _context = cgCreateContext();
    CgLog::Log("create content", _context);
    cgGLSetDebugMode(CG_TRUE);
    cgSetParameterSettingMode(_context,CG_DEFERRED_PARAMETER_SETTING);
    CgLog::Log("selecting vertex profile", _context);

    _lightAngle = -0.4;
    _lightColor = Vector3f(1,1,1);
     
    _lightKc = 0.4f;
    _lightKl = 0.1f;
    _lightKq = 0.03f;
    _InitMaterial();
}