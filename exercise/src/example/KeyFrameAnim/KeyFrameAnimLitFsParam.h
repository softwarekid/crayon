#ifndef knight_fs_lit_Param_h__
#define knight_fs_lit_Param_h__
#include <CgShaderParametersBase.h>

class KeyFrameAnimLitFsParam : public CgShaderParametersBase
{
private:
    CGparameter factorScalar;
    CGparameter decal;

public:
    void SetScaleFactor(const float xFactor, const float yFactor);
    void SetTexture(GLuint name);
    void ExtractParams() override;
    void EnableTexture();
    void DisableTexture();

    explicit KeyFrameAnimLitFsParam(const CgShader& shader);
};


#endif

