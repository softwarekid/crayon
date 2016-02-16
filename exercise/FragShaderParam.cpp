#include "FragShaderParam.h"

void FragShaderParam::SetKeCoef(const Vector3f& value)
{
    _Set3fvParam(_keParam, value);
}

void FragShaderParam::SetKaCoef(const Vector3f& value)
{
    _Set3fvParam(_kaParam, value);
}

void FragShaderParam::SetKdCoef(const Vector3f& value)
{
    _Set3fvParam(_kdParam, value);
}

void FragShaderParam::SetKsCoef(const Vector3f& value)
{
    _Set3fvParam(_ksParam, value);
}

void FragShaderParam::SetShinessCoef(const float value)
{
    _Set1fParam(_shininess, value);
}

void FragShaderParam::SetLightPosition(const Vector3f& value)
{
    _Set3fvParam(_lightPosition, value);
}

void FragShaderParam::Init()
{
    _GetProgramParam(_keParam, "");
    _GetProgramParam(_kaParam, "");
    _GetProgramParam(_kdParam, "");
    _GetProgramParam(_ksParam, "");
    _GetProgramParam(_globleAmbient, "");
    _GetProgramParam(_lightColor, "");
    _GetProgramParam(_lightPosition, "");
    _GetProgramParam(_shininess, "");
}

FragShaderParam::FragShaderParam(const CgShader shader)
{
    _context = shader.GetContext();
    _program = shader.GetProgram();
}