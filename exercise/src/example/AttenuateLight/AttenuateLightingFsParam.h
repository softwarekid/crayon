#ifndef attenuate_lighting_fs_param_h_
#define attenuate_lighting_fs_param_h_
#include <CgShaderParametersBase.h>
class AttenuateLightingFsParam : public CgShaderParametersBase
{
private:
    CGparameter eyePosition;
    CGparameter globalAmbient;
    CGparameter lightPosition;
    CGparameter lightColor;
    CGparameter lightAttenKc;
    CGparameter lightAttenKl;
    CGparameter lightAttenKq;
    CGparameter materialKe;
    CGparameter materialKa;
    CGparameter materialKd;
    CGparameter materialKs;
    CGparameter materialShininess;

public:
    void SetEyePosition(const Vector3f& eyePos_);
    void SetGlobalAmbient(const Vector3f& ga_);
    void SetLightPos(const Vector3f& lightPos_);
    void SetLightColor(const Vector3f& lightColor_);
    void SetLightAttenKc(const float lightAttenKc_);
    void SetLightAttenKl(const float lightAttenKl_);
    void SetLightAttenKq(const float lightAttenKq_);
    void SetMaterialKe(const Vector3f& ke_);
    void SetMaterialKa(const Vector3f& ka_);
    void SetMaterialKd(const Vector3f& kd_);
    void SetMaterialKs(const Vector3f& ks_);
    void SetMaterialShininess(const float shininess_);

    void ExtractParams() override;

    explicit AttenuateLightingFsParam(const CgShader shader);
};

#endif