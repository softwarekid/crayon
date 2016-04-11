#include "BulgeLightDrawCall.h"

void BulgeLightDrawCall::_SetMaterial(const Material& m)
{
    
}

void BulgeLightDrawCall::Draw(const Camera& camera, const Vector4f& rotation, const Vector3f& translate, const Vector3f& eyePos, const Vector3f& lightPosition, const Material& m, std::function<void()> draw)
{
    //_SetMaterial(m);
    _transform.SetCamera(camera);
    _transform.SetArbitraryRotation(rotation[1], rotation[2], rotation[3], rotation[4]);
    _transform.SetTranslate(translate.x, translate.y, translate.z);

    Matrix4f modelViewProjMatix;
    _transform.GetMVPMatrix(modelViewProjMatix);
    _vertParam->SetMVPMatrix(modelViewProjMatix);
    // deferred params are updated, aka, perform a draw call
    _vertShader->UpdateParams();
    _fragShader->UpdateParams();
    draw();
}

BulgeLightDrawCall::BulgeLightDrawCall(CGcontext content, CGprofile vertProfile, CGprofile fragProfile, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry) :CgDrawPass(content, vertProfile, fragProfile, vertFileName, vertEntry, fragFilename, fragEntry)
{
    _vertParam = new BulgeLightVsParam(*_vertShader);
    _fragParam = new BulgeLightFsParam(*_fragShader);

    _vertParam->ExtractParams();
}

BulgeLightDrawCall::~BulgeLightDrawCall()
{
    delete _vertParam;
    _vertParam = nullptr;
    delete _fragParam;
    _fragParam = nullptr;
}