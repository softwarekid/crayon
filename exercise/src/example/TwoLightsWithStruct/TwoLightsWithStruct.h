#ifndef two_lights_with_struct
#define two_lights_with_struct
#include "GlutWrapper.h"
#include "TwoLightsWithStructVsParam.h"
#include "TwoLightsWithStructFsParam.h"
class TwoLightsWithStruct : public GlutWrapper
{
private:
    TwoLightsWithStructVsParam* _vertParams;
    TwoLightsWithStructFsParam* _fragParams;
    float _lightAngles[2] = { -0.4, -0.1 };
    Vector3f _lightColors[2] = { Vector3f(0.95, 0.95, 0.95), Vector3f(0.5, 0.5, 0.2) };
    void _SetBrassMaterial();
    void _SetPlasticMaterial();
    void _SetEmissiveOnly(int lightIndex);
protected:
    void _Idle() override;
    void _Display(void) override;
    void _InitVertShader() override;
    void _InitFragShader() override;
public:
    TwoLightsWithStruct(const char* title, int width, int height);
};

#endif
