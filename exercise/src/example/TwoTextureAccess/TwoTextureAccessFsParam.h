#ifndef two_texture_access_fs_param__
#define two_texture_access_fs_param__
#include <CgShaderParametersBase.h>
#include <CgShader.h>

class TwoTextureAccessFsParam : public CgShaderParametersBase
{
private:
    CGparameter decal;

public:
    void EnableTexture();
    void DisableTexture();
    void SetTexture(GLuint name);
    void ExtractParams() override;
    explicit TwoTextureAccessFsParam(const CgShader& shader);
};

#endif
