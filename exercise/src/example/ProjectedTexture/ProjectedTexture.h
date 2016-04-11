#ifndef prjected_texture_h__
#include <GlutWrapper.h>
#include "ProjectedTextureDrawPass.h"

class ProjectedTexture : public GlutWrapper
{
private:
    ProjectedTextureDrawPass* drawPass;

public:
    ProjectedTexture();
    ~ProjectedTexture();
};
#endif // !prjected_texture_h__
