#ifndef two_texture_access_vs_param__
#define two_texture_access_vs_param__
#include <CgShaderParametersBase.h>

class TwoTextureAccessVsParam : public CgShaderParametersBase
{
private:
    CGparameter _leftSeperation;
    CGparameter _rightSeperation;

public:
    void SetLeftSeperation(const Vector3f& value);
    void SetRightSeperation(const Vector3f& value);

    explicit TwoTextureAccessVsParam(const CgShader& shader);

};

#endif

