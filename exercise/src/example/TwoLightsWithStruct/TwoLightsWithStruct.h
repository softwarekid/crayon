#ifndef two_lights_with_struct
#define two_lights_with_struct
#include "GlutWrapper.h"
#include "TwoLightsWithStructVsParam.h"
#include "TwoLightsWithStructFsParam.h"
#include "Material.h"
#include <vector>

class TwoLightsWithStruct : public GlutWrapper
{
private:
    TwoLightsWithStructVsParam* _vertParams;
    TwoLightsWithStructFsParam* _fragParams;
    float _lightAngles[2];
    Vector3f _lightColors[2];
    Material brassMaterial;
    Material redPlasticMaterial;
    Material emissiveMaterial[2];

    void _SetBrassMaterial();
    void _SetRedPlasticMaterial();
    void _SetEmissiveOnly(int lightIndex);
    void _InitMaterial();
    void _SetMaterial(const Material& m);
    void _Draw(const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const std::vector<Vector3f>& lightPostions, const Material& m, RenderObject obj );
protected:
    void _Idle() override;
    void _Display(void) override;
    void _InitVertShader() override;
    void _InitFragShader() override;
    void _InitLightColor();
public:
    TwoLightsWithStruct(const char* title, int width, int height);
};

#endif
