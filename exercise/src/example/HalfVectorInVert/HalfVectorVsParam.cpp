#include "HalfVectorVsParam.h"

void HalfVectorVsParam::SetMVPMatrix(const Matrix4f& value)
{
    _setMatrix4fParam(MVP, value);
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