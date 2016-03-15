#ifndef cg_program_h__
#define cg_program_h__
#include "CgShader.h"
#include "CgShaderParametersBase.h"
#include <functional>
#include <Material.h>
#include <Transform.h>

class CgProgram
{
protected:
    CgShader* _vertShader;
    CgShader* _fragShader;
    Transform _transform;
    Vector3f _MatVecMulReduced(const Matrix4f& matrix, const Vector4f& vector);
public:
    void virtual InitConstShaderParams() = 0;
    void virtual Draw(const Camera& camera, const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw){};
    void virtual _SetMaterial(const Material& m) = 0;
    CgProgram(CGcontext content, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry);
    virtual ~CgProgram();
};


#endif