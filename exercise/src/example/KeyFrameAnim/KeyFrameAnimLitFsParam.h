#ifndef knight_fs_lit_Param_h__
#define knight_fs_lit_Param_h__
#include <CgShaderParametersBase.h>

class KeyFrameAnimLitFsParam : public CgShaderParametersBase
{
private:
    CGparameter factorScalar;
    CGparameter texture;

public:
    void SetFactorScalar(const float factor);
    void SetTexture(GLuint name);
    void ExtractParams() override;

    explicit KeyFrameAnimLitFsParam(const CgShader& shader);
};


#endif

