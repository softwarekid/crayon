#ifndef bulge_h__
#define  bulge_h__
#include "GlutWrapper.h"
#include "BulgeVsParam.h"
#include "BulgeFsParam.h"
#include "BulgeLightFsParam.h"
#include "BulgeLightVsParam.h"
#include "Material.h"
#include <functional>

class Bulge : public GlutWrapper
{
private:

    //BulgeVsParam* _vertParams;
    //BulgeFsParam* _fragParams;
    //CgShader* _lightVertexShader;
    //CgShader* _lightFragShader;
    BulgeLightVsParam* _lightVsParam;
    BulgeLightFsParam* _lightFsParam;

    float _time;
    float _lightAngle;

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
};
#endif