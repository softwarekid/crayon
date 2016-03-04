#ifndef attenuate_lighting_vs_param_h_
#define attenuate_lighting_vs_param_h_
#include <CgShaderParametersBase.h>
class AttenuateLightingVsParam : public CgShaderParametersBase
{
private:
    CGparameter MVPMatrix;
public:
    void SetMVPMatrix(const Matrix4f& value);
    void ExtractParams() override;
    explicit AttenuateLightingVsParam(const CgShader& shader);
};

#endif
