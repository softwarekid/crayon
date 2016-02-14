#include "VertShaderParam.h"

void VertShaderParam::Init()
{
}

VertShaderParam::VertShaderParam(const CgShader& shader)
{
    _context = shader.GetContext();
    _program = shader.GetProgram();
}