#ifndef TransformGtest_h__
#define TransformGtest_h__
#include "Transform.h"

class TransformGTest:public GtestBase
{
protected:
    void SetUp()
    {
        Camera c(Vector3f(0,0,-10), Vector3f(0,0,0), Vector3f(0,1,0));
        t.SetCamera(c);
        t.SetTranslate(2,0,0);
        t.SetArbitraryRotation(45,1,0,0);
        t.SetProjection(60, 1, 0.3, 1000);
    }

    Transform t;
    Matrix4f modelTrans;
    Matrix4f viewTrans;
    Matrix4f projTrans;
    Matrix4f MVTrans;
    Matrix4f MVPTrans;
    Vector4f result;
};

TEST_F(TransformGTest, ModelMatrix)
{
    t.GetModelMatrix(modelTrans);
    result = modelTrans.Mul(Vector4f(1,2,1,1));
    IsVectorEQ(result, Vector4f(3.0f, 0.707106531f, 2.12132049f,1.0f));
}

TEST_F(TransformGTest, ViewMatrix)
{
    t.GetViewMatrix(viewTrans);
    result = viewTrans.Mul(Vector4f(1 , 2, 1, 1));
    IsVectorEQ(result, Vector4f(-1, 2.0f, -11, 1.0f));
}

TEST_F(TransformGTest, ProjMatrix)
{
    t.GetProjMatrix(projTrans);
    result = projTrans.Mul(Vector4f(1,2,1,1));
    result.reduceTo3DSpace();
    IsVectorEQ(result, Vector4f(-1.73205078f,-3.46410155f,1.60078025f,1));
}

TEST_F(TransformGTest, MVMatrix)
{
    //t.GetModelMatrix(modelTrans);
    t.GetMVMatrix(MVTrans);
    result = MVTrans.Mul(Vector4f(1,2,1,1));
    IsVectorEQ(result, Vector4f(-3, 0.707106531f, -12.1213207f, 1));
}

TEST_F(TransformGTest, MVPMatrix)
{
    t.GetMVPMatrix(MVPTrans);
    result = MVPTrans.Mul(Vector4f(1,2,1,1));
    result.reduceTo3DSpace();
    IsVectorEQ(result, Vector4f(-0.4286787f, 0.101040505f, 0.951085746f, 1));
}
#endif