#include "HalfVectorVsParam.h"

void HalfVectorVsParam::SetMVPMatrix(const Matrix4f& value)
{
    _setMatrix4fParam(MVP, value);
}

void HalfVectorVsParam::Init()
{
    _GetProgramParam(MVP, "modelViewProj");
    _GetProgramParam(lightPosition, "lightPosition");
    _GetProgramParam(eyePosition, "eyePosition");
}

HalfVectorVsParam::HalfVectorVsParam(const CgShader& shader) : CgShaderParametersBase(shader.GetContext(), shader.GetProgram())
{
}