#ifndef Knight_Vs_h__
#define Knight_Vs_h__
#include <CgShaderParametersBase.h>

class KeyFrameAnimLitVsParam : public CgShaderParametersBase
{
private:
    CGparameter _modelViewProj;
    CGparameter _eyePosition;
    CGparameter _lightPosition;
    CGparameter _lightColor;
    CGparameter _shininess;
    CGparameter _blend;

public:

    void SetMVPMatrix(const Matrix4f& matrix);
    void SetEyePosition(const Vector3f& eyePos);
    void SetLightPos(const Vector3f& lightPos);
    void SetLightColor(const Vector3f& lightColor);
    void SetShininess(const float shininess);
    void SetBlendCoef(const float blendCoef);

    void ExtractParams() override;
    explicit KeyFrameAnimLitVsParam(const CgShader& shader);
};
#endif // !Knight_Vs_h__