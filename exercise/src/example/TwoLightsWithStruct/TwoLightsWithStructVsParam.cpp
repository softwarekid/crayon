#include "TwoLightsWithStructVsParam.h"

void TwoLightsWithStructVsParam::SetMVPMatrix(const Matrix4f& matrix)
{
    _setMatrix4fParam(modelViewProj, matrix);
}

void TwoLightsWithStructVsParam::SetEyePosition(const Vector3f& eyePos)
{
    _Set3fvParam(eyePosition, eyePos);
}

void TwoLightsWithStructVsParam::SetGlobalAmbient(const Vector3f& ga)
{
    _Set3fvParam(globalAmbient, ga);
}

void TwoLightsWithStructVsParam::SetLightPos(int index, const Vector3f& lightPos)
{
    _Set3fvParam(lightPositions[index], lightPos);
}

void TwoLightsWithStructVsParam::SetLightColor(int index, const Vector3f& lightColor)
{
    _Set3fvParam(lightColors[index], lightColor);
}

void TwoLightsWithStructVsParam::SetMaterialKe(const Vector3f& ke)
{
    _Set3fvParam(materialKe, ke);
}

void TwoLightsWithStructVsParam::SetMaterialKa(const Vector3f& ka)
{
    _Set3fvParam(materialKa, ka);
}

void TwoLightsWithStructVsParam::SetMaterialKd(const Vector3f& kd)
{
    _Set3fvParam(materialKd, kd);
}

void TwoLightsWithStructVsParam::SetMaterialKs(const Vector3f& ks)
{
    _Set3fvParam(materialKs, ks);
}

void TwoLightsWithStructVsParam::SetMaterialShininess(const float shininess)
{
    _Set1fParam(materialShininess, shininess);
}

void TwoLightsWithStructVsParam::ExtractParams()
{
    _GetProgramParam(modelViewProj, "modelViewProj");
    _GetProgramParam(eyePosition, "eyePosition");
    _GetProgramParam(globalAmbient, "globalAmbient");
    _GetProgramParam(lightPositions[0], "lights[0].position");
    _GetProgramParam(lightPositions[1], "lights[1].position");
    _GetProgramParam(lightColors[0], "lights[0].color");
    _GetProgramParam(lightColors[1], "lights[1].color");
    _GetProgramParam(materialKe, "material.Ke");
    _GetProgramParam(materialKa, "material.Ka");
    _GetProgramParam(materialKd, "material.Kd");
    _GetProgramParam(materialKs, "material.Ks");
    _GetProgramParam(materialShininess, "material.shininess");
}

TwoLightsWithStructVsParam::TwoLightsWithStructVsParam(const CgShader& shader) : CgShaderParametersBase(shader)
{

}