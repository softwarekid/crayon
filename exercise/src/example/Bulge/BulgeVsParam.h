#ifndef bulge_vs_param_h__
#define bulge_vs_param_h__
#include <CgShaderParametersBase.h>
class BulgeVsParam : public CgShaderParametersBase
{
private:
    CGparameter modelViewProj;
    CGparameter eyePosition;
    CGparameter lightPosition;
    CGparameter lightColor;
    CGparameter kd;
    CGparameter shininess;
    
public:
    void SetMVPMatrix(const Matrix4f& matrix);
    void SetEyePosition(const Vector3f& eyePos);
    void SetLightPos(const Vector3f& lightPos);
    void SetLightColor(const Vector3f& lightColor1);
    void SetKd(const Vector3f& kd);
    void SetShininess(const float shininess);

    void ExtractParams() override;
};

#endif