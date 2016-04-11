#ifndef pojected_texture_h__
#include <CgShaderParametersBase.h>

class ProjectedTextureVsParam : public CgShaderParametersBase
{
private:
    CGparameter MVPModel;

public:
    void SetMVPMatrix(const Matrix4f& matrix);
    void ExtractParams() override;
    explicit ProjectedTextureVsParam(const CgShader& shader);
};

#endif // !pojected_texture_h__
