#include "KnightDrawCall.h"

void KnightDrawCall::Draw(const Camera& camrea, const Vector4f& rotation, const Vector3f& translate, const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw)
{
    
}

KnightDrawCall::KnightDrawCall(CGcontext content, CGprofile vertProfile, CGprofile fragProfile, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry) :CgDrawCall(content, vertProfile, fragProfile,vertFileName,vertEntry,fragFilename,fragEntry)
{

}