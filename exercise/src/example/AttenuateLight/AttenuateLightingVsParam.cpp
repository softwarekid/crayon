#include "AttenuateLightingVsParam.h"

void AttenuateLightingVsParam::SetMVPMatrix(const Matrix4f& value)
{
    _setMatrix4fParam(MVPMatrix, value);
}

void AttenuateLightingVsParam::ExtractParams()
{
    _GetProgramParam(MVPMatrix, "MVPMatrix");
}

AttenuateLightingVsParam::AttenuateLightingVsParam(const CgShader& shader) : CgShaderParametersBase(shader)
{
}