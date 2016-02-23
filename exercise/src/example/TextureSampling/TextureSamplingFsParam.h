#ifndef texture_sampling_fs_param__
#define texture_sampling_fs_param__
#include <CgShaderParametersBase.h>
#include <CgShader.h>

class TextureSamplingFsParam : public CgShaderParametersBase
{
private:
    CGparameter decal;

public:
    void SetTexture(GLuint name) override;
    void ExtractParams() override;
    explicit TextureSamplingFsParam(const CgShader& shader);
};

#endif