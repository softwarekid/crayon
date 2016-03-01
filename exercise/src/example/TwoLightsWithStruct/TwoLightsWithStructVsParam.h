#ifndef two_lights_with_struct_vs_param
#define two_lights_with_struct_vs_param
#include <CgShaderParametersBase.h>
class TwoLightsWithStructVsParam : public CgShaderParametersBase
{
private:
    CGparameter modelViewProj;
    CGparameter eyePosition;
    CGparameter globalAmbient;
    CGparameter lightPositions[2];
    CGparameter lightColors[2];
    CGparameter materialKe;
    CGparameter materialKa;
    CGparameter materialKd;
    CGparameter materialKs;
    CGparameter materialShininess;

public:

    // the parameters will affect a draw call, so usually they are put in the display function 
    void SetMVPMatrix(const Matrix4f& matrix);
    void SetEyePosition(const Vector3f& eyePos);
    void SetGlobalAmbient(const Vector3f& ga);
    void SetLightPos(int index, const Vector3f& lightPos1);
    void SetLightColor(int index, const Vector3f& lightColor1);
    void SetMaterialKe(const Vector3f& ke);
    void SetMaterialKa(const Vector3f& ka);
    void SetMaterialKd(const Vector3f& kd);
    void SetMaterialKs(const Vector3f& ks);
    void SetMaterialShininess(const float shininess);

    void ExtractParams() override;


    TwoLightsWithStructVsParam(const CgShader& shader);
};
#endif
