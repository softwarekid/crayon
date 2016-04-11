#ifndef knight_draw_call_h__
#define knight_draw_call_h__
#include "KeyFrameAnimLitVsParam.h"
#include "KeyFrameAnimLitFsParam.h"
#include "CgDrawCall.h"

//���������������shader �Ĳ���������drawʲô���ɳ�����ָ���ġ�
class KnightDrawCall : public CgDrawCall
{
private:
    float _blendParam;
    KeyFrameAnimLitVsParam* _vertParam;
    KeyFrameAnimLitFsParam* _fragParam;

    void _SetMaterial(const Material& m) override{};

public:
    void SetConstParams(const Vector3f& lightColor, GLuint textureName,const float xScale, const float yScale);
    void SetVaringParams(const Camera& camrea, const Vector4f& rotation, const Vector3f& translate,const Vector3f& eyePos, const Vector3f& lightPosition, const float blendFactor);
    void Draw(std::function<void()> doDraw);
    KnightDrawCall(CGcontext content, CGprofile vertProfile, CGprofile fragProfile, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry);
    ~KnightDrawCall();
};


#endif