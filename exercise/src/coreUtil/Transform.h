#ifndef transform_h__
#define transform_h__
#include "Matrix.h"
#include "Camera.h"
// todo: refractor this class, camera and model-view transform ought to be seperate
class Transform
{
public:
    Transform();
    void SetTranslate(float x, float y, float z);
    void SetArbitraryRotation(float angle, float axisX, float axisY, float axisZ);
    void SetArbitraryRotation(float angle, Vector3f axis);
    void SetAxisAngles(float xDegree, float yDegree, float zDegree);
    void SetCamera(const Camera camera);
    void SetProjection(float fov, float aspectRatio, float zNear, float zFar);

    int GetModelMatrix(Matrix4f& modelMatrix);
    int GetViewMatrix(Matrix4f& viewMatrix);
    int GetProjMatrix(Matrix4f& projMatrix);
    int GetMVMatrix(Matrix4f& modelViewMatrix);
    int GetMVPMatrix(Matrix4f& MVPMatrix);

private:
    Camera _camera;
    Matrix4f _translateMatrix;
    Matrix4f _rotateMatrix;
    Matrix4f _projectionMatrix;
    Matrix4f _modelMatrix;
    Matrix4f _viewMatrix;
    Matrix4f _modelViewMatrix;
    Matrix4f _modelViewProjMatrix;
    bool _transRotTranDirty;
    bool _viewDirty;
    bool _projDirty;
    bool _MVDirty;
    bool _MVPDirty;

private:
    bool _CanModelMatrixRead();
    bool _CanViewMatrixRead();
    bool _CanProjMatrixRead();
    bool _CanMVMatrixRead();
    bool _CanMVPMatrixRead();
};

#endif