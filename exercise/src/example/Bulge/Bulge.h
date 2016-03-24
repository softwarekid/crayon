#ifndef bulge_h__
#define  bulge_h__
#include "GlutWrapper.h"
#include "SceneShaderProgram.h"
#include "BulgeLight.h"
#include "Material.h"
#include <functional>

class Bulge : public GlutWrapper
{
private:

    SceneShaderProgram* _sceneProgram;
    BulgeLight* _lightPrgoram;
    float _time;
    float _lightAngle;
    const std::string sceneVertShaderName = R"(src\example\Bulge\bulge_V.cg)";
    const std::string sceneFragShaderName = R"(src\example\Bulge\bulge_F.cg)";
    const std::string lightVertShaderName = R"(src\example\Bulge\bulgeLight_V.cg)";
    const std::string lightFragShaderName = R"(src\example\Bulge\bulgeLight_F.cg)";
    const std::string vertEntry = R"(main_v)";
    const std::string fragEntry = R"(main_f)";
    Material redMaterial;
    Material greenMaterial;
    Material emptyMaterial;
    void _InitMaterial();
    void _InitConstShaderParams();
    void _SetMaterial(Material m);
    void _Draw(const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw);
protected:
    void _Idle() override;
    void _Display(void) override;
public:
    Bulge(const char* title, int width, int height);
    ~Bulge();

};
#endif