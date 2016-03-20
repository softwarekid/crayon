#include "SceneShaderProgram.h"
#include <functional>
#include <Material.h>
#include <Camera.h>

void SceneShaderProgram::SetTime(float time)
{
    _vertParam->SetTime(time);
}

void SceneShaderProgram::InitConstShaderParams()
{
    _vertParam->SetLightColor(Vector3f(0.95f, 0.95f, 0.95f));
    _vertParam->SetScaleFactor(0.3f);
    _vertParam->SetFrequency(2.4f);
}

void SceneShaderProgram::_SetMaterial(const Material& m)
{
    _vertParam->SetKd(m.kd);
    _vertParam->SetShininess(m.shininess);
}

void SceneShaderProgram::Draw(const Camera& camera, const Vector4f& rotation, const Vector3f& translate, const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw)
{
    _SetMaterial(m);
    _transform.SetCamera(camera);
    _transform.SetArbitraryRotation(rotation[1], rotation[2], rotation[3], rotation[4]);
    _transform.SetTranslate(translate.x, translate.y, translate.z);
    Matrix4f modelMatrix;
    _transform.GetModelMatrix(modelMatrix);
    //TODO can I use rvalue-reference here?
    Matrix4f invModelMatrix = modelMatrix.Invert();

    Vector3f objSpaceEyePosition = _MatVecMulReduced(invModelMatrix, eyePos);
    _vertParam->SetEyePosition(objSpaceEyePosition);
    Vector3f objSpaceLightPosition = _MatVecMulReduced(invModelMatrix, lightPosition);
    _vertParam->SetLightPos(objSpaceLightPosition);
    Matrix4f modelViewProjMatix;
    _transform.GetMVPMatrix(modelViewProjMatix);
    _vertParam->SetMVPMatrix(modelViewProjMatix);
    // deferred params are updated, aka, perform a draw call
    _vertShader->UpdateParams();
    _fragShader->UpdateParams();
    draw();
}

SceneShaderProgram::SceneShaderProgram(CGcontext content, CGprofile vertProfile, CGprofile fragProfile,std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry) : CgProgramWrapper(content, vertProfile, fragProfile, vertFileName, vertEntry, fragFilename, fragEntry)
{
    _vertParam = new BulgeVsParam(*_vertShader);
    _fragParam = new BulgeFsParam(*_fragShader);

    _vertParam->ExtractParams();
    _fragParam->ExtractParams();
}

SceneShaderProgram::~SceneShaderProgram()
{
    delete _vertParam;
    _vertParam = nullptr;
    delete _fragParam;
    _fragParam = nullptr;
}