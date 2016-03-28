#include "KeyFrameAnimLitFsParam.h"
#include <CG/cgGL.h>


void KeyFrameAnimLitFsParam::SetScaleFactor(const float xScale, const float yScale)
{
    _Set2fParam(factorScalar, xScale, yScale);
}

void KeyFrameAnimLitFsParam::SetTexture(GLuint name)
{
    _SetTextureParam(decal, name);
}

void KeyFrameAnimLitFsParam::ExtractParams()
{
    _GetProgramParam(factorScalar, "scaleFactor");
    _GetProgramParam(decal, "decal");
}

void KeyFrameAnimLitFsParam::EnableTexture()
{
    cgGLEnableTextureParameter(decal);
}

void KeyFrameAnimLitFsParam::DisableTexture()
{
    cgGLDisableTextureParameter(decal);
}

KeyFrameAnimLitFsParam::KeyFrameAnimLitFsParam(const CgShader& shader) : CgShaderParametersBase(shader)
{
    
}