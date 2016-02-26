#ifndef frag_shader_param__
#define frag_shader_param__
#include <CgShaderParametersBase.h>
#include <CgShader.h>

class HalfVectorFsParam : public CgShaderParametersBase
{
private:
    CGparameter _ke;
    CGparameter _ka;
    CGparameter _kd;
    CGparameter _ks;
    CGparameter _globleAmbient;
    CGparameter _lightColor;
    CGparameter _lightPosition;
    CGparameter _shininess;

public:
    void SetKeCoef(const Vector3f& value) ;
    void SetKaCoef(const Vector3f& value) ;
    void SetKdCoef(const Vector3f& value) ;
    void SetKsCoef(const Vector3f& value) ;
    void SetShinessCoef(const float value);
    void SetLightPosition(const Vector3f& value);
    void SetLightColor(const Vector3f& value) ;
    //void SetEyePostion(const Vector3f& value) override;
    void ExtractParams() ;

    HalfVectorFsParam(const CGcontext context, const CGprogram program);
    explicit HalfVectorFsParam(const CgShader& shader);
};
#endif