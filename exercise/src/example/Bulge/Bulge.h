#ifndef bulge_h__
#define  bulge_h__
#include "GlutWrapper.h"
#include "BulgeVsParam.h"
#include "BulgeFsParam.h"
#include "BulgeLightFsParam.h"
#include "BulgeLightVsParam.h"
#include "SceneShaderProgram.h"
#include "Material.h"
#include <functional>

class Bulge : public GlutWrapper
{
private:

    //BulgeVsParam* _vertParams;
    //BulgeFsParam* _fragParams;
    //CgShader* _lightVertexShader;
    //CgShader* _lightFragShader;
    //BulgeLightVsParam* _lightVsParam;
    //BulgeLightFsParam* _lightFsParam;
    SceneShaderProgram* _sceneProgram;
    float _time;
    float _lightAngle;
    const std::string sceneVertShaderName = R"(src\example\Bulge\bulge_V.cg)";
    const std::string sceneFragShaderName = R"(src\example\Bulge\bulge_F.cg)";
    const std::string vertEntry = R"(main_v)";
    const std::string fragEntry = R"(main_f)";
    Material redMaterial;
    Material greenMaterial;
    void _InitMaterial();
    void _InitConstShaderParams();
    void _SetMaterial(Material m);
    void _Draw(const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw);
protected:
    void _Idle() override;
    void _Display(void) override;
    void _InitVertShader() override;
    void _InitFragShader() override;

public:
    Bulge(const char* title, int width, int height);
    ~Bulge();

};
#endif