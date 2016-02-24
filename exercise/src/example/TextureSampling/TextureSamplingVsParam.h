#ifndef texture_sampling_vs_param__
#define texture_sampling_vs_param__
#include <CgShaderParametersBase.h>
#include <CgShader.h>

class TextureSamplingVsParam : public CgShaderParametersBase
{
public:
    explicit TextureSamplingVsParam(const CgShader& shader);
};
#endif
