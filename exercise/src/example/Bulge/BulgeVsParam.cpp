#include "BulgeVsParam.h"

void BulgeVsParam::SetMVPMatrix(const Matrix4f& matrix)
{
    _setMatrix4fParam(modelViewProj, matrix);
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

}