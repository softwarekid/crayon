#ifndef bulge_h__
#define  bulge_h__
#include "GlutWrapper.h"
#include "SceneDrawCall.h"
#include "BulgeLightDrawCall.h"
#include "Material.h"

class Bulge : public GlutWrapper
{
private:
    SceneDrawCall* _sceneProgram;
    BulgeLightDrawCall* _lightPrgoram;
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
protected:
    void _Idle() override;
    void _Display(void) override;
public:
    Bulge(const char* title, int width, int height);
    ~Bulge();

};
#endif