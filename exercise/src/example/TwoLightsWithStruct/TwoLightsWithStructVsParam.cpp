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

void TwoLightsWithStructVsParam::SetLightPos1(const Vector3f& lightPos1)
{
    _Set3fvParam(lightPosition[0], lightPos1);
}

void TwoLightsWithStructVsParam::SetLightPos2(const Vector3f& lightPos2)
{
    _Set3fvParam(lightPosition[1], lightPos2);
}

void TwoLightsWithStructVsParam::SetLightColor1(const Vector3f& lightColor1)
{
    _Set3fvParam(lightColor[0], lightColor1);
}

void TwoLightsWithStructVsParam::SetLightColor2(const Vector3f& lightColor2)
{
    _Set3fvParam(lightColor[1], lightColor2);
}

void TwoLightsWithStructVsParam::SetMaterialKe(const float ke)
{
    _Set1fParam(materialKe, ke);
}

void TwoLightsWithStructVsParam::SetMaterialKa(const float ka)
{
    _Set1fParam(materialKa, ka);
}

void TwoLightsWithStructVsParam::SetMaterialKd(const float kd)
{
    _Set1fParam(materialKd, kd);
}

void TwoLightsWithStructVsParam::SetMaterialKs(const float ks)
{
    _Set1fParam(materialKs, ks);
}

void TwoLightsWithStructVsParam::SetMaterialShininess(const float shininess)
{
    _Set1fParam(materialShininess, shininess);
}

void TwoLightsWithStructVsParam::ExtractParams()
{
    cgGetNamedParameter(modelViewProj, );
    cgGetNamedParameter(eyePosition, );
    cgGetNamedParameter(globalAmbient, );
    cgGetNamedParameter(lightPosition[0], );
    cgGetNamedParameter(lightPosition[1], );
    cgGetNamedParameter(lightColor[0], );
    cgGetNamedParameter(lightColor[1], );
    cgGetNamedParameter(materialKe, );
    cgGetNamedParameter(materialKa, );
    cgGetNamedParameter(materialKd, );
    cgGetNamedParameter(materialKs, );
    cgGetNamedParameter(materialShininess, );
}

TwoLightsWithStructVsParam::TwoLightsWithStructVsParam(const CgShader& shader) : CgShaderParametersBase(shader)
{

}