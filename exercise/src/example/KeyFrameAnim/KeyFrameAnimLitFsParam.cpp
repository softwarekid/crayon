#include "KeyFrameAnimLitFsParam.h"

void KeyFrameAnimLitFsParam::SetFactorScalar(const float factor)
{
    _Set1fParam(factorScalar, factor);
}

void KeyFrameAnimLitFsParam::SetTexture(GLuint name)
{
    _SetTextureParam(texture, name);
}

void KeyFrameAnimLitFsParam::ExtractParams()
{
    _GetProgramParam(factorScalar, "scaleFactor");
    _GetProgramParam(texture, "decal");
}

KeyFrameAnimLitFsParam::KeyFrameAnimLitFsParam(const CgShader& shader) : CgShaderParametersBase(shader)
{

}