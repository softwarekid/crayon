#include "VertShaderParam.h"

void VertShaderParam::SetMVPMatrix(const Matrix4f& value)
{
    _setMatrix4fParam(MVP, value);
}

void VertShaderParam::Init()
{
}

VertShaderParam::VertShaderParam(const CgShader& shader)
{
    _context = shader.GetContext();
    _program = shader.GetProgram();
}