#ifndef cg_program_h__
#define cg_program_h__
#include "CgShader.h"
#include "CgShaderParametersBase.h"
#include <functional>
struct Material;

class CgProgram
{
private:
    CgShaderParametersBase* _vertParam;
    CgShaderParametersBase* _fragParam;

protected:
    CgShader* _vertShader;
    CgShader* _fragShader;
public:
    void virtual InitConstShaderParams() = 0;
    void virtual Draw(const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw);
    void virtual SetMaterial(const Material& m) = 0;
    CgProgram(CGcontext content, CGprofile profile, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry);
    virtual ~CgProgram();
};


#endif