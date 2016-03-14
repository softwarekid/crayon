#include "BulgeVsParam.h"

void BulgeVsParam::SetMVPMatrix(const Matrix4f& matrix)
{
    _setMatrix4fParam(modelViewProj, matrix);
}

void BulgeVsParam::SetTime(const float time_)
{
    _Set1fParam(time, time_);
}

void BulgeVsParam::SetFrequency(const float frequency_)
{
    _Set1fParam(frequency, frequency_);
}

void BulgeVsParam::SetScaleFactor(const float sFactor)
{
    _Set1fParam(scaleFactor, sFactor);
}

void BulgeVsParam::SetEyePosition(const Vector3f& eyePos)
{
    _Set3fvParam(eyePosition, eyePos);
}

void BulgeVsParam::SetLightPos(const Vector3f& lightPos)
{
    _Set3fvParam(lightPosition, lightPos);
}

void BulgeVsParam::SetLightColor(const Vector3f& lightColor_)
{
    _Set3fvParam(lightColor, lightColor_);
}

void BulgeVsParam::SetKd(const Vector3f& kd_)
{
    _Set3fvParam(kd, kd_);
}

void BulgeVsParam::SetShininess(const float shininess_)
{
    _Set1fParam(shininess, shininess_);
}

void BulgeVsParam::ExtractParams()
{
    _GetProgramParam(modelViewProj, "modelViewProj");
    _GetProgramParam(time, "time");
    _GetProgramParam(frequency, "frequency");
    _GetProgramParam(scaleFactor, "scaleFactor");
    _GetProgramParam(kd, "kd");
    _GetProgramParam(shininess, "shininess");
    _GetProgramParam(eyePosition, "eyePos");
    _GetProgramParam(lightPosition, "lightPos");
    _GetProgramParam(lightColor, "lightColor");
}

BulgeVsParam::BulgeVsParam(const CgShader& shader) : CgShaderParametersBase(shader)
{
}