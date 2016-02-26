#include "TwoTextureAccessFsParam.h"
#include <CG/cgGL.h>

void TwoTextureAccessFsParam::EnableTexture()
{
    cgGLEnableTextureParameter(decal);
}

void TwoTextureAccessFsParam::DisableTexture()
{
    cgGLDisableTextureParameter(decal);
}

void TwoTextureAccessFsParam::SetTexture(GLuint name)
{
    _SetTextureParam(decal, name);
}

void TwoTextureAccessFsParam::ExtractParams()
{
    _GetProgramParam(decal, "decal");
}

TwoTextureAccessFsParam::TwoTextureAccessFsParam(const CgShader& shader) :CgShaderParametersBase(shader)
{
}