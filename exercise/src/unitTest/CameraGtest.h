#ifndef CameraGtest_h__
#define CameraGtest_h__
//#include "GtestBase.h"
#include "Camera.h"
#include "GtestBase.h"

class CameraGtest: public GtestBase
{
protected:
    virtual void SetUp()
    {
        camera.SetExtrinsicParams(Vector3f(0,0,-10), Vector3f(0,0,0),Vector3f(0,1,0));
    }

    Camera camera;
};

TEST_F(CameraGtest, viewMatrix)
{
    Matrix4f viewMatrix;;
    camera.GetViewMatrix(viewMatrix);
    Vector4f result = viewMatrix.Mul(Vector4f(1,0,0,1));
    IsVectorEQ(result, Vector4f(-1,0,-10,1));
}

#endif
