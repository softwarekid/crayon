#include "Matrix.h"
#include "Camera.h"

class Transform
{
public:
    Transform();
    void SetTranslate(float x, float y, float z);
    void SetRotation(float angle, float axisX, float axisY, float axisZ);
    void SetCamera(const Camera camera);
    void SetProjection(float fov, float aspectRatio, float zNear, float zFar);

    int GetModelMatrix(Matrix4f& modelMatrix);
    int GetViewMatrix(Matrix4f& viewMatrix);
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
    bool _transRotUpdated;
    bool _modelCahed;
    bool _viewCached;
    bool _prjCached;
    bool _MVCached;
    bool _MVPCached;

private:
    bool _CanModelMatrixRead();
    bool _CanViewMatrixRead();
    bool _CanMVMatrixRead();
    bool _CanMVPMatrixRead();
};