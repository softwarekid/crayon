#ifndef attenuate_lighting_h_
#define attenuate_lighting_h_
#include "GlutWrapper.h"
#include "AttenuateLightingVsParam.h"
#include "AttenuateLightingFsParam.h"
#include <Material.h>

class AttenateLighting : public GlutWrapper
{
private:
    AttenuateLightingVsParam* _vertParams;
    AttenuateLightingFsParam* _fragParams;

    float _lightKc;
    float _lightKl;
    float _lightKq;
    float _lightAngle ;
    Vector3f _lightColor;
    Material _brassMaterial;
    Material _redPlasticMaterial;
    Material _greenEmeraldMaterial;
    Material _emissiveMaterial;
    Vector3f _globleAmbient;

    void _Draw(const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPostion, const Material& m, RenderObject obj );
    void _RenderObject(RenderObject mesh);
    void _SetMaterial(const Material& m);
    void _SetLightIntrinsicParam();
    void _InitMaterial();
protected:
    void _Idle() override;
    void _Display(void) override;
    void _InitVertShader() override;
    void _InitFragShader() override;

public:
    AttenateLighting(const char* title, int width, int height);
};

#endif