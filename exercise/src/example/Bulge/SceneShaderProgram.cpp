#include "SceneShaderProgram.h"

void SceneShaderProgram::InitConstShaderParams()
{
    _vertParam->SetLightColor(Vector3f(0.95f, 0.95f, 0.95f));
    _vertParam->SetScaleFactor(0.3);
    _vertParam->SetFrequency(2.4);
}

void SceneShaderProgram::SetMaterial(const Material& m)
{
    _vertParam->SetKd(m.kd);
    _vertParam->SetShininess(m.shininess);
}

void SceneShaderProgram::Draw(const Vector4f& rotation, const Vector3f& translate, const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw)
{

}

SceneShaderProgram::SceneShaderProgram(CGcontext content, CGprofile profile, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry) : CgProgram(content, profile, vertFileName, vertEntry, fragFilename, fragEntry)
{
    _vertParam = new BulgeVsParam(*_vertShader);
    _fragParam = new BulgeFsParam(*_fragParam);

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