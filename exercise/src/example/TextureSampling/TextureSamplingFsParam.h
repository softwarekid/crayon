#ifndef texture_sampling_fs_param__
#define texture_sampling_fs_param__
#include <CgShaderParametersBase.h>
#include <CgShader.h>

class TextureSamplingFsParam : public CgShaderParametersBase
{
private:
    CGparameter decal;

public:
    void EnableTexture();
    void DisableTexture();
    void SetTexture(GLuint name);
    void ExtractParams() ;
    explicit TextureSamplingFsParam(const CgShader& shader);
};

#endif