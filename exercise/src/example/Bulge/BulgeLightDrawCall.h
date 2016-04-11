#ifndef bulge_Light_h__
#define bulge_Light_h__
#include "BulgeLightFsParam.h"
#include "BulgeLightVsParam.h"
#include "CgDrawPass.h"

class BulgeLightDrawCall : public CgDrawPass
{
private:
    BulgeLightFsParam* _fragParam;
    BulgeLightVsParam* _vertParam;

    void _SetMaterial(const Material& m) override;
public :
    void Draw(const Camera& camrea, const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw) override;
    BulgeLightDrawCall(CGcontext content, CGprofile vertProfile, CGprofile fragProfile,std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry);
    ~BulgeLightDrawCall();

};

#endif