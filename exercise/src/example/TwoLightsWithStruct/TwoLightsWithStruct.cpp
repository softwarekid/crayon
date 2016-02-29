#include <assert.h>
#include "TwoLightsWithStruct.h"
#include <CG/cgGL.h>
#include <vector>
using namespace std;

void TwoLightsWithStruct::_SetBrassMaterial()
{
    _vertParams->SetMaterialKe(Vector3f(0.0, 0.0, 0.0));
    _vertParams->SetMaterialKa(Vector3f(0.33, 0.22, 0.03));
    _vertParams->SetMaterialKd(Vector3f(0.78, 0.57, 0.11));
    _vertParams->SetMaterialKs(Vector3f(0.99, 0.91, 0.81));
    _vertParams->SetMaterialShininess(27.8);
}

void TwoLightsWithStruct::_SetPlasticMaterial()
{
    _vertParams->SetMaterialKe(Vector3f(0.0, 0.0, 0.0));
    _vertParams->SetMaterialKa(Vector3f(0.0, 0.0, 0.0));
    _vertParams->SetMaterialKd(Vector3f(0.5, 0.0, 0.0));
    _vertParams->SetMaterialKs(Vector3f(0.7, 0.6, 0.6));
    _vertParams->SetMaterialShininess(32.0);
}

void TwoLightsWithStruct::_SetEmissiveOnly(int lightIndex)
{
    assert(lightIndex >= 0 && lightIndex <= 1);
    Vector3f zero(0, 0, 0);
    _vertParams->SetMaterialKe(_lightColors[lightIndex]);
    _vertParams->SetMaterialKa(zero);
    _vertParams->SetMaterialKd(zero);
    _vertParams->SetMaterialKs(zero);
    _vertParams->SetMaterialShininess(0);
}

void TwoLightsWithStruct::_Idle()
{

}

void TwoLightsWithStruct::_Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const Vector3f eyePosition(0, 0, 13);
    const Vector3f eyeCenter(0, 0, 0);
    const Vector3f eyeUp(0, 1, 0);
    const vector<Vector3f> lightPositions{Vector3f(5 * sin(_lightAngles[0]), 1.5, 5 * cos(_lightAngles[0])),
                                          Vector3f(5 * sin(_lightAngles[1]), 0.25, 5 * cos(_lightAngles[1]))};
    _vertShader->BindProgram();
    _vertShader->EnableProfile();
    _fragShader->BindProgram();
    _fragShader->EnableProfile();

    Camera camera(eyePosition, eyeCenter, eyeUp);
    _transform.SetCamera(camera);
    
    _SetBrassMaterial();

    _transform.SetArbitraryRotation(70, 1, 1, 1);
    _transform.SetTranslate(2, 0, 0);
    Matrix4f modelMatrix;
    _transform.GetModelMatrix(modelMatrix);

    //TODO can I use rvalue-reference here?
    Matrix4f invModelMatrix = modelMatrix.Invert();

    Vector3f objSpaceEyePosition = _MatVecMulReduced(invModelMatrix, eyePosition);
    _vertParams->SetEyePosition(objSpaceEyePosition);
    //Vector4f objSpaceLightPosition = invModelMatrix.Mul(lightPosition);

    ///* Transform world-space eye and light positions to sphere's object-space. */
    //transform(objSpaceEyePosition, invModelMatrix, eyePosition);
    //cgSetParameter3fv(myCgVertexParam_eyePosition, objSpaceEyePosition);
    //for (i = 0; i<2; i++) {
    //    transform(objSpaceLightPosition, invModelMatrix, lightPosition[i]);
    //    cgSetParameter3fv(myCgVertexParam_lightPosition[i], objSpaceLightPosition);
    //}

    ///* modelViewMatrix = viewMatrix * modelMatrix */
    //multMatrix(modelViewMatrix, viewMatrix, modelMatrix);

    ///* modelViewProj = projectionMatrix * modelViewMatrix */
    //multMatrix(modelViewProjMatrix, myProjectionMatrix, modelViewMatrix);

    ///* Set matrix parameter with row-major matrix. */
    //cgSetMatrixParameterfr(myCgVertexParam_modelViewProj, modelViewProjMatrix);
    //cgUpdateProgramParameters(myCgVertexProgram);
    //glutSolidSphere(2.0, 40, 40);


}

void TwoLightsWithStruct::_InitVertShader()
{
    auto profileVertex = cgGLGetLatestProfile(CG_GL_VERTEX);
    string fileName(R"(src\example\TwoLightsWithStruct\TwoLightsWithStruct_V.cg)");
    string entry("main_v");
    _vertShader = new CgShader(_context, profileVertex, fileName, entry);
    _vertParams = new TwoLightsWithStructVsParam(*_vertShader);
    _vertParams->ExtractParams();
    cgGLSetOptimalOptions(profileVertex);
}

void TwoLightsWithStruct::_InitFragShader()
{
    auto profileFrag = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    string fileName(R"(src\example\TwoLightsWithStruct\TwoLightsWithStruct_F.cg)");
    string entry("main_f");
    _fragShader = new CgShader(_context, profileFrag, fileName, entry);
    _fragParams = new TwoLightsWithStructFsParam(*_fragShader);
    _fragParams->ExtractParams();
    cgGLSetOptimalOptions(profileFrag);
}

TwoLightsWithStruct::TwoLightsWithStruct(const char* title, int width, int height) : GlutWrapper(title, width, height)
{
    _lightAngles[0] = -0.4;
    _lightAngles[1] = -0.1;

    _lightColors[0] = Vector3f(0.95, 0.95, 0.95);
    _lightColors[1] = Vector3f(0.5, 0.5, 0.2);
}