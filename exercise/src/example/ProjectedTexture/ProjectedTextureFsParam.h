#ifndef projected_texture_h__
#include <CgShaderParametersBase.h>

class ProjectedTextureFsParam: public CgShaderParametersBase
{
private:
public:
    explicit ProjectedTextureFsParam(const CgShader& shader);
};
#endif // !projected_texture_h__
