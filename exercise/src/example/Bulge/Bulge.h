#ifndef bulge_h__
#define  bulge_h__
#include "GlutWrapper.h"
#include "BulgeVsParam.h"
#include "BulgeFsParam.h"
#include "BulgeLightFsParam.h"
#include "BulgeLightVsParam.h"
#include "Material.h"
#include <GL/glut.h>

class Bulge : public GlutWrapper
{
private:
    class SphereDrawer
    {
    public:
        void operator()()
        {
            glutSolidSphere(2.0, 40, 40);
        }
    };

    class TorusDrawer
    {
    public:
        void operator()()
        {
            glutSolidTorus(0.15, 1.7, 40, 40);
        }
    };

    class lightDrawer
    {
    public:
        void operator()()
        {
            glutSolidSphere(0.1, 12, 12);
        }
    };

    BulgeVsParam* _vertParams;
    BulgeFsParam* _fragParams;
    CgShader* _lightVertexShader;
    CgShader* _lightFragShader;
    BulgeLightVsParam* _lightVsParam;
    BulgeLightFsParam* _lightFsParam;

    float _time;
    float _lightAngle;

    Material redMaterial;
    Material greenMaterial;
    void _InitMaterial();
    void _InitConstShaderParams();
    void _SetMaterial(Material m);
    SphereDrawer _sphereDrawer;
    TorusDrawer _torusDrawer;
    lightDrawer _lightDrawer;
    template<class C> void _Draw(const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, C draw );
protected:
    void _Idle() override;
    void _Display(void) override;
    void _InitVertShader() override;
    void _InitFragShader() override;

public:
    Bulge(const char* title, int width, int height);
};

template <class C>
void Bulge::_Draw(const Vector4f& rotation, const Vector3f& translate, const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, C draw)
{
    _SetMaterial(m);
    _transform.SetArbitraryRotation(rotation[1], rotation[2], rotation[3], rotation[4]);
    _transform.SetTranslate(translate.x, translate.y, translate.z);
    Matrix4f modelMatrix;
    _transform.GetModelMatrix(modelMatrix);
    //TODO can I use rvalue-reference here?
    Matrix4f invModelMatrix = modelMatrix.Invert();

    Vector3f objSpaceEyePosition = _MatVecMulReduced(invModelMatrix, eyePos);
    _vertParams->SetEyePosition(objSpaceEyePosition);
    Vector3f objSpaceLightPosition = _MatVecMulReduced(invModelMatrix, lightPosition);
    _vertParams->SetLightPos(objSpaceLightPosition);
    Matrix4f modelViewProjMatix;
    _transform.GetMVPMatrix(modelViewProjMatix);
    _vertParams->SetMVPMatrix(modelViewProjMatix);
    // deferred params are updated, aka, perform a draw call
    _vertShader->UpdateParams();
    _fragShader->UpdateParams();
    draw();
}

#endif