#include "KnightVsLitParam.h"

void KnightVsLitParam::SetMVPMatrix(const Matrix4f& matrix)
{
    _setMatrix4fParam(_modelViewProj, matrix);
}

void KnightVsLitParam::SetEyePosition(const Vector3f& eyePos)
{
    _Set3fvParam(_eyePosition, eyePos);
}

void KnightVsLitParam::SetLightPos(const Vector3f& lightPos)
{
    _Set3fvParam(_lightPosition, lightPos);
}

void KnightVsLitParam::SetLightColor(const Vector3f& lightColor)
{
    _Set3fvParam(_lightColor, lightColor);
}

void KnightVsLitParam::SetShininess(const float shininess)
{
    _Set1fParam(_shininess, shininess);
}

void KnightVsLitParam::SetBlendCoef(const float blendCoef)
{
    _Set1fParam(_blendCoef, blendCoef);
}

void KnightVsLitParam::ExtractParams()
{

}

KnightVsLitParam::KnightVsLitParam(const CgShader& shader) :CgShaderParametersBase(shader)
{
}