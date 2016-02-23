#include "TextureSamplingFsParam.h"

void TextureSamplingFsParam::SetTexture(GLuint name)
{
    _SetTextureParam(decal, name);
}

void TextureSamplingFsParam::ExtractParams()
{
    _GetProgramParam(decal, "decal");
}

TextureSamplingFsParam::TextureSamplingFsParam(const CgShader& shader) : CgShaderParametersBase(shader)
{
}