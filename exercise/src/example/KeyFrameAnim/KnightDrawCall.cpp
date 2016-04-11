#include "KnightDrawCall.h"

void KnightDrawCall::SetConstParams(const Vector3f& lightColor,GLuint textureName,const float xScale, const float yScale)
{
    _vertParam->SetLightColor(Vector3f(1.0f, 1.0f, 1.0f));
    _vertParam->SetShininess(8.0f);
    _fragParam->SetTexture(textureName);
    _fragParam->SetScaleFactor(xScale, yScale);
}

void KnightDrawCall::SetVaringParams(const Camera& camrea, const Vector4f& rotation, const Vector3f& translate, const Vector3f& eyePos, const Vector3f& lightPosition, const float blendFactor)
{
    _transform.SetCamera(camrea);
    _transform.SetArbitraryRotation(rotation[1], rotation[2], rotation[3], rotation[4]);
    _transform.SetTranslate(translate.x, translate.y, translate.z);
    Matrix4f modelMatrix;
    _transform.GetModelMatrix(modelMatrix);
    //TODO can I use rvalue-reference here?
    Matrix4f invModelMatrix = modelMatrix.Invert();

    Vector3f objSpaceEyePosition = _MatVecMulReduced(invModelMatrix, eyePos);
    _vertParam->SetEyePosition(objSpaceEyePosition);
    Vector3f objSpaceLightPosition = _MatVecMulReduced(invModelMatrix, lightPosition);
    _vertParam->SetLightPos(objSpaceLightPosition);
    Matrix4f modelViewProjMatix;
    _transform.GetMVPMatrix(modelViewProjMatix);
    _vertParam->SetMVPMatrix(modelViewProjMatix);
    _vertParam->SetBlendFactor(blendFactor);

    // deferred params are updated, aka, perform a draw call
    _vertShader->UpdateParams();
    _fragShader->UpdateParams();
}

void KnightDrawCall::Draw(std::function<void()> doDraw)
{
    _fragParam->EnableTexture();
    doDraw();
    _fragParam->DisableTexture();
}

KnightDrawCall::KnightDrawCall(CGcontext content, CGprofile vertProfile, CGprofile fragProfile, std::string vertFileName, std::string vertEntry, std::string fragFilename, std::string fragEntry) :CgDrawCall(content, vertProfile, fragProfile,vertFileName,vertEntry,fragFilename,fragEntry)
{
    _vertParam = new KeyFrameAnimLitVsParam(*_vertShader);
    _fragParam = new KeyFrameAnimLitFsParam(*_fragShader);
    _vertParam->ExtractParams();
    _fragParam->ExtractParams();
}

KnightDrawCall::~KnightDrawCall()
{
    delete _vertParam;
    _vertParam = nullptr;
    delete _fragParam;
    _fragParam = nullptr;
}