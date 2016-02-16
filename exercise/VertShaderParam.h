#ifndef vert_param__
#define vert_param__
#include "CgShaderParametersBase.h"
#include "CgShader.h"


class VertShaderParam:public CgShaderParametersBase
{
private:
    CGparameter MVP;

public:

    void SetMVPMatrix(const Matrix4f& value) override;
    void Init() override;

    VertShaderParam(const CgShader& shader);
};
#endif