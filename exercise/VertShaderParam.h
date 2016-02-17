#ifndef vert_param__
#define vert_param__
#include "CgShaderParametersBase.h"
#include "CgShader.h"


class VertShaderParam:public CgShaderParametersBase
{
private:
    CGparameter MVP;
    CGparameter lightPosition;
    CGparameter eyePosition;

public:

    void SetMVPMatrix(const Matrix4f& value) override;
    void Init() override;

    explicit VertShaderParam(const CgShader& shader);
};
#endif