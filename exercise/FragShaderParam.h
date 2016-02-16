#ifndef frag_shader_param__
#define frag_shader_param__
#include "CgShaderParametersBase.h"
#include "CgShader.h"

class FragShaderParam : public CgShaderParametersBase
{
private:
    CGparameter _keParam;
    CGparameter _kaParam;
    CGparameter _kdParam;
    CGparameter _ksParam;
    CGparameter _globleAmbient;
    CGparameter _lightColor;
    CGparameter _lightPosition;
    CGparameter _shininess;

public:
    void SetKeCoef(const Vector3f& value) override;
    void SetKaCoef(const Vector3f& value) override;
    void SetKdCoef(const Vector3f& value) override;
    void SetKsCoef(const Vector3f& value) override;
    void SetShinessCoef(const float value) override;
    void SetLightPosition(const Vector3f& value) override;
    //void SetEyePostion(const Vector3f& value) override;
    void Init() override;

    explicit FragShaderParam(const CgShader shader);
};
#endif
