#ifndef two_texture_access_vs_param__
#define two_texture_access_vs_param__
#include <CgShaderParametersBase.h>
#include <CgShader.h>

class TwoTextureAccessVsParam : public CgShaderParametersBase
{
private:
    CGparameter _leftSeperation;
    CGparameter _rightSeperation;

public:
    void SetLeftSeperation(float x, float y);
    void SetRightSeperation(float x, float y);
    void ExtractParams() override;
    explicit TwoTextureAccessVsParam(const CgShader& shader);
};

#endif

