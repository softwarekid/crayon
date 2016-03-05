#include "AttenuateLightingFsParam.h"

void AttenuateLightingFsParam::SetEyePosition(const Vector3f& eyePos)
{
    _Set3fvParam(eyePosition, eyePos);
}

void AttenuateLightingFsParam::SetGlobalAmbient(const Vector3f& ga)
{
    _Set3fvParam(globalAmbient, ga);
}

void AttenuateLightingFsParam::SetLightPos(const Vector3f& lightPos)
{
    _Set3fvParam(lightPosition, lightPos);
}

void AttenuateLightingFsParam::SetLightColor(const Vector3f& lightColor_)
{
    _Set3fvParam(lightColor, lightColor_);
}

void AttenuateLightingFsParam::SetLightAttenKc(const float lightAttenKc_)
{
    _Set1fParam(lightAttenKc, lightAttenKc_);
}

void AttenuateLightingFsParam::SetLightAttenKl(const float lightAttenKl_)
{
    _Set1fParam(lightAttenKl, lightAttenKl_);
}

void AttenuateLightingFsParam::SetLightAttenKq(const float lightAttenKq_)
{
    _Set1fParam(lightAttenKq, lightAttenKq_);
}

void AttenuateLightingFsParam::SetMaterialKe(const Vector3f& ke_)
{
    _Set3fvParam(materialKe, ke_);
}

void AttenuateLightingFsParam::SetMaterialKa(const Vector3f& ka_)
{
    _Set3fvParam(materialKa, ka_);
}

void AttenuateLightingFsParam::SetMaterialKd(const Vector3f& kd_)
{
    _Set3fvParam(materialKd, kd_);
}

void AttenuateLightingFsParam::SetMaterialKs(const Vector3f& ks_)
{
    _Set3fvParam(materialKs, ks_);
}

void AttenuateLightingFsParam::SetMaterialShininess(const float shininess_)
{
    _Set1fParam(materialShininess, shininess_);
}

void AttenuateLightingFsParam::ExtractParams()
{
    _GetProgramParam(eyePosition, "eyePosition");
    _GetProgramParam(globalAmbient, "globalAmbient");
    _GetProgramParam(lightPosition, "light.position");
    _GetProgramParam(lightColor, "light.color");
    _GetProgramParam(lightAttenKc, "light.kc");
    _GetProgramParam(lightAttenKl, "light.kl");
    _GetProgramParam(lightAttenKq, "light.kq");
    _GetProgramParam(materialKe, "material.Ke");
    _GetProgramParam(materialKa, "material.Ka");
    _GetProgramParam(materialKd, "material.Kd");
    _GetProgramParam(materialKs, "material.Ks");
    _GetProgramParam(materialShininess, "material.shininess");
}

AttenuateLightingFsParam::AttenuateLightingFsParam(const CgShader& shader) : CgShaderParametersBase(shader)
{
}