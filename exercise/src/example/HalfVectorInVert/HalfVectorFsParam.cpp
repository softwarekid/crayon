#include "HalfVectorFsParam.h"

void HalfVectorFsParam::SetKeCoef(const Vector3f& value)
{
    _Set3fvParam(_ke, value);
}

void HalfVectorFsParam::SetKaCoef(const Vector3f& value)
{
    _Set3fvParam(_ka, value);
}

void HalfVectorFsParam::SetKdCoef(const Vector3f& value)
{
    _Set3fvParam(_kd, value);
}

void HalfVectorFsParam::SetKsCoef(const Vector3f& value)
{
    _Set3fvParam(_ks, value);
}

void HalfVectorFsParam::SetShinessCoef(const float value)
{
    _Set1fParam(_shininess, value);
}

void HalfVectorFsParam::SetLightPosition(const Vector3f& value)
{
    _Set3fvParam(_lightPosition, value);
}

void HalfVectorFsParam::SetLightColor(const Vector3f& value)
{
    _Set3fvParam(_lightColor, value);
}

void HalfVectorFsParam::ExtractParams()
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

HalfVectorFsParam::HalfVectorFsParam(const CGcontext context, const CGprogram program) : CgShaderParametersBase(context,program)
{

}

//HalfVectorFsParam::HalfVectorFsParam(const CgShader& shader) : CgShaderParametersBase(shader.GetContext(), shader.GetProgram())
HalfVectorFsParam::HalfVectorFsParam(const CgShader& shader) : CgShaderParametersBase(shader)
{
}