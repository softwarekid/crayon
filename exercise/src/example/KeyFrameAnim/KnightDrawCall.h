#ifndef knight_draw_call_h__
#define knight_draw_call_h__
#include "CgDrawCall.h"

class KnightDrawCall : public CgDrawCall
{
private:
    

public:
    void Draw(const Camera& camrea, const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw) override;
    KnightDrawCall(CGcontext content, CGprofile vertProfile, CGprofile fragProfile, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry);
};


#endif