#ifndef two_texture_access_fs_param__
#define two_texture_access_fs_param__
#include <CgShaderParametersBase.h>

class TwoTextureAccessFsParam : public CgShaderParametersBase
{
private:
    CGparameter decal;

public:
    void EnableTexture() override;
    void DisableTexture() override;
    void SetTexture(GLuint name) override;
    void ExtractParams() override;
    explicit TwoTextureAccessFsParam(const CgShader& shader);
};

#endif
