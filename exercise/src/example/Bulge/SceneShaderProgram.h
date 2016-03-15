#ifndef scene_shader_progarm_h__
#define scene_shader_progarm_h__
#include "CgProgram.h"
#include "BulgeFsParam.h"
#include "BulgeVsParam.h"
class SceneShaderProgram : public CgProgram
{
private:
    BulgeFsParam* _fragParam;
    BulgeVsParam* _vertParam;

public:
    void InitConstShaderParams() override;
    void SetMaterial(const Material& m) override;
    void Draw(const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw) override;
    SceneShaderProgram(CGcontext content, CGprofile profile, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry);
    ~SceneShaderProgram();
};

#endif
