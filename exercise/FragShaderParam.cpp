#include "FragShaderParam.h"

void FragShaderParam::SetKeCoef(const Vector3f& value)
{
    _Set3fvParam(_ke, value);
}

void FragShaderParam::SetKaCoef(const Vector3f& value)
{
    _Set3fvParam(_ka, value);
}

void FragShaderParam::SetKdCoef(const Vector3f& value)
{
    _Set3fvParam(_kd, value);
}

void FragShaderParam::SetKsCoef(const Vector3f& value)
{
    _Set3fvParam(_ks, value);
}

void FragShaderParam::SetShinessCoef(const float value)
{
    _Set1fParam(_shininess, value);
}

void FragShaderParam::SetLightPosition(const Vector3f& value)
{
    _Set3fvParam(_lightPosition, value);
}

void FragShaderParam::SetLightColor(const Vector3f& value)
{
    _Set3fvParam(_lightColor, value);
}

void FragShaderParam::Init()
{
    _GetProgramParam(_globleAmbient, "globalAmbient");
    _GetProgramParam(_lightColor, "lightColor");
    _GetProgramParam(_lightPosition, "lightPosition");
    _GetProgramParam(_ke, "Ke");
    _GetProgramParam(_ka, "Ka");
    _GetProgramParam(_kd, "Kd");
    _GetProgramParam(_ks, "Ks");
    _GetProgramParam(_shininess, "shininess");
}

FragShaderParam::FragShaderParam(const CGcontext context, const CGprogram program) : CgShaderParametersBase(context,program)
{

}

FragShaderParam::FragShaderParam(const CgShader& shader) : CgShaderParametersBase(shader.GetContext(), shader.GetProgram())
{
}