#include "VertShaderParam.h"

void VertShaderParam::SetMVPMatrix(const Matrix4f& value)
{
    _setMatrix4fParam(MVP, value);
}

void VertShaderParam::Init()
{
    _GetProgramParam(MVP, "modelViewProj");
    _GetProgramParam(lightPosition, "lightPosition");
    _GetProgramParam(eyePosition, "eyePosition");
}

VertShaderParam::VertShaderParam(const CgShader& shader) : CgShaderParametersBase(shader.GetContext(), shader.GetProgram())
{
}