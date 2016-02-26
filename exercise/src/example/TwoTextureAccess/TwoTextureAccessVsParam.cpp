#include "TwoTextureAccessVsParam.h"

void TwoTextureAccessVsParam::SetLeftSeperation(float x, float y)
{
    _Set2fParam(_leftSeperation, x, y);
}

void TwoTextureAccessVsParam::SetRightSeperation(float x, float y)
{
    _Set2fParam(_rightSeperation, x, y);
}

void TwoTextureAccessVsParam::ExtractParams()
{
    _GetProgramParam(_leftSeperation, "leftSeperation");
    _GetProgramParam(_rightSeperation, "rightSeperation");
}

TwoTextureAccessVsParam::TwoTextureAccessVsParam(const CgShader& shader) :CgShaderParametersBase(shader)
{

}