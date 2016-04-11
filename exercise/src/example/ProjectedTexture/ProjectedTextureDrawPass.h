#ifndef projected_texture_draw_pass_h__
#include <CgDrawPass.h>
#include "ProjectedTextureFsParam.h"
#include "ProjectedTextureVsParam.h"

class ProjectedTextureDrawPass : public CgDrawPass
{
private:
    ProjectedTextureVsParam* _vertParam;
    ProjectedTextureFsParam* _fragParam;
    void _SetMaterial(const Material& m) override;
public:
    ProjectedTextureDrawPass(CGcontext content, CGprofile vertProfile, CGprofile fragProfile,std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry);
    ~ProjectedTextureDrawPass();
};
#endif // !projected_texture_draw_pass_h__