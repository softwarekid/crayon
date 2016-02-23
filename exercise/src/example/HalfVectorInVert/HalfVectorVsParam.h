#ifndef half_vector_vs_params__
#define half_vector_vs_params__
#include <CgShaderParametersBase.h>
#include <CgShader.h>


class HalfVectorVsParam:public CgShaderParametersBase
{
private:
    CGparameter MVP;
    CGparameter lightPosition;
    CGparameter eyePosition;

public:

    void SetMVPMatrix(const Matrix4f& value) override;
    void Init() override;

    explicit HalfVectorVsParam(const CgShader& shader);
};
#endif