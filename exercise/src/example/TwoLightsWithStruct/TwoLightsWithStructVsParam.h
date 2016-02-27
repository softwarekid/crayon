#ifndef two_lights_with_struct_vs_param
#define two_lights_with_struct_vs_param
#include <CgShaderParametersBase.h>
class TwoLightsWithStructVsParam : public CgShaderParametersBase
{
private:
    CGparameter modelViewProj;
    CGparameter eyePosition;
    CGparameter globalAmbient;
    CGparameter lightPosition[2];
    CGparameter lightColor[2];
    CGparameter materialKe;
    CGparameter materialKa;
    CGparameter materialKd;
    CGparameter materialKs;
    CGparameter materialShininess;

public:

    void SetMVPMatrix(const Matrix4f& matrix);
    void SetEyePosition(const Vector3f& eyePos);
    void SetGlobalAmbient(const Vector3f& ga);
    void SetLightPos1(const Vector3f& lightPos1);
    void SetLightPos2(const Vector3f& lightPos2);
    void SetLightColor1(const Vector3f& lightColor1);
    void SetLightColor2(const Vector3f& lightColor2);
    void SetMaterialKe(const float ke);
    void SetMaterialKa(const float ka);
    void SetMaterialKd(const float kd);
    void SetMaterialKs(const float ks);
    void SetMaterialShininess(const float shininess);

    TwoLightsWithStructVsParam(const CgShader& shader);
};
#endif
