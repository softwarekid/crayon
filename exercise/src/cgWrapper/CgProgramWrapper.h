#ifndef cg_program_h__
#define cg_program_h__
#include "CgShader.h"
#include "CgShaderParametersBase.h"
#include <functional>
#include <Material.h>
#include <Transform.h>

class CgDrawCall
{
protected:
    void virtual _SetMaterial(const Material& m) = 0;
    CgShader* _vertShader;
    CgShader* _fragShader;
    Transform _transform;
    Vector3f _MatVecMulReduced(const Matrix4f& matrix, const Vector4f& vector);
public:
    void BindShader();
    void EnableProfile();
    void DisableProfile();
    void SetProjection(float fov, float aspectRatio, float zNear, float zFar);
    void virtual InitConstShaderParams(){};
    void virtual Draw(const Camera& camera, const Vector4f& rotation, const Vector3f& translate, const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw){};
    CgDrawCall(CGcontext content, CGprofile vertProfile, CGprofile fragProfile, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry);
    virtual ~CgDrawCall();
};


#endif