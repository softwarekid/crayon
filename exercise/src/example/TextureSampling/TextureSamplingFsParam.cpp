#include "TextureSamplingFsParam.h"
#include <CG/cgGL.h>

void TextureSamplingFsParam::EnableTexture()
{
    cgGLEnableTextureParameter(decal);
}

void TextureSamplingFsParam::DisableTexture()
{
    cgGLDisableTextureParameter(decal);
}

// 
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