#include "HalfVectorVsParam.h"

void HalfVectorVsParam::SetMVPMatrix(const Matrix4f& value)
{
    _setMatrix4fParam(MVP, value);
}

void HalfVectorVsParam::SetLightPosition(const Vector3f& value)
{
    _Set3fvParam(lightPosition, value);
}

void HalfVectorVsParam::SetEyePostion(const Vector3f& value)
{
    _Set3fvParam(eyePosition, value);
}

void HalfVectorVsParam::ExtractParams()
{
    _GetProgramParam(MVP, "modelViewProj");
    _GetProgramParam(lightPosition, "lightPosition");
    _GetProgramParam(eyePosition, "eyePosition");
}

//HalfVectorVsParam::HalfVectorVsParam(const CgShader& shader) : CgShaderParametersBase(shader.GetContext(), shader.GetProgram())
HalfVectorVsParam::HalfVectorVsParam(const CgShader& shader) : CgShaderParametersBase(shader)
{
}