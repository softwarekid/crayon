#include "KeyFrameAnimLitVsParam.h"

void KeyFrameAnimLitVsParam::SetMVPMatrix(const Matrix4f& matrix)
{
    _setMatrix4fParam(_modelViewProj, matrix);
}

void KeyFrameAnimLitVsParam::SetEyePosition(const Vector3f& eyePos)
{
    _Set3fvParam(_eyePosition, eyePos);
}

void KeyFrameAnimLitVsParam::SetLightPos(const Vector3f& lightPos)
{
    _Set3fvParam(_lightPosition, lightPos);
}

void KeyFrameAnimLitVsParam::SetLightColor(const Vector3f& lightColor)
{
    _Set3fvParam(_lightColor, lightColor);
}

void KeyFrameAnimLitVsParam::SetShininess(const float shininess)
{
    _Set1fParam(_shininess, shininess);
}

void KeyFrameAnimLitVsParam::SetBlendCoef(const float blendCoef)
{
    _Set1fParam(_blend, blendCoef);
}

void KeyFrameAnimLitVsParam::ExtractParams()
{
    _GetProgramParam(_modelViewProj, "modelViewProj");
    _GetProgramParam(_blend, "keyFrameBlend");
    _GetProgramParam(_eyePosition, "eyePos");
    _GetProgramParam(_lightPosition, "lightPos");
    _GetProgramParam(_lightColor, "lightColor");
    _GetProgramParam(_shininess, "shininess");
}

KeyFrameAnimLitVsParam::KeyFrameAnimLitVsParam(const CgShader& shader) :CgShaderParametersBase(shader)
{
}