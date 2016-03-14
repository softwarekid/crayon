#ifndef bugle_light_h__
#define bugle_light_h__
#include <CgShaderParametersBase.h>
class BulgeLightVsParam : CgShaderParametersBase
{
private:
    CGparameter modelViewProj;
public:
    void SetMVPMatrix(const Matrix4f& matrix);
    void ExtractParams() override;
    explicit BulgeLightVsParam(const CgShader& shader);
};

#endif