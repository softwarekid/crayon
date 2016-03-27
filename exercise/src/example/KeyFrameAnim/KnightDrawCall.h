#ifndef knight_draw_call_h__
#define knight_draw_call_h__
#include "KeyFrameAnimLitVsParam.h"
#include "CgDrawCall.h"

//���������������shader �Ĳ���������drawʲô���ɳ�����ָ���ġ�
class KnightDrawCall : public CgDrawCall
{
private:
    float _blendParam;
    KeyFrameAnimLitVsParam* _vertParam;

public:
    void SetBlendParam(float blend);
    void SetConstParams();
    void SetVaringParams();
    void Draw(const Camera& camrea, const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw) override;
    KnightDrawCall(CGcontext content, CGprofile vertProfile, CGprofile fragProfile, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry);
};


#endif