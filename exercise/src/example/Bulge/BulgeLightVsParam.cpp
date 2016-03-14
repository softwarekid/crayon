#include "BulgeLightVsParam.h"

void BulgeLightVsParam::SetMVPMatrix(const Matrix4f& matrix)
{
    _setMatrix4fParam(modelViewProj, matrix);
}

void BulgeLightVsParam::ExtractParams()
{
    _GetProgramParam(modelViewProj, "modelViewProj");
}

BulgeLightVsParam::BulgeLightVsParam(const CgShader& shader) : CgShaderParametersBase(shader)
{

}