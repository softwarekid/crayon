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

    void _SetMaterial(const Material& m) override;
public:
    void SetTime(float time);
    void InitConstShaderParams() override;
    void Draw(const Camera& camrea, const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw) override;
    SceneShaderProgram(CGcontext content, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry);
    ~SceneShaderProgram();
};

#endif
