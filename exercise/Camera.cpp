#include "Camera.h"
#include "Constants.h"
using namespace Constants;
Camera::Camera()
{
    _viewMatrix.SetZero();
}

Camera::Camera(const Vector3f& eyePos, const Vector3f& center,const Vector3f& up)
{
    SetExtrinsicParams(eyePos, center, up);
}

void Camera::SetExtrinsicParams(const Vector3f& eyePos, const Vector3f& center, const Vector3f& up)
{
    // build the uvn viewing-coordinate reference
    Vector3f n = eyePos - center;
    n.Normalized();
    Vector3f u = up.Cross(n);
    u.Normalized();
    Vector3f v = n.Cross(u);

    _viewMatrix(1, 1) = u.x;
    _viewMatrix(1, 2) = u.y;
    _viewMatrix(1, 3) = u.z;
    _viewMatrix(1, 4) = -eyePos.x * u.x - eyePos.y * u.y - eyePos.z * u.z;

    _viewMatrix(2, 1) = v.x;
    _viewMatrix(2, 2) = v.y;
    _viewMatrix(2, 3) = v.z;
    _viewMatrix(2, 4) = -eyePos.x * v.x - eyePos.y * v.y - eyePos.z * v.z;

    _viewMatrix(3, 1) = n.x;
    _viewMatrix(3, 2) = n.y;
    _viewMatrix(3, 3) = n.z;
    _viewMatrix(3, 4) = -eyePos.x * n.x - eyePos.y * n.y - eyePos.z * n.z;
    _viewMatrix(4, 4) = 1.0f;
}

int Camera::GetViewMatrix(Matrix4f& viewMatrix)
{
    viewMatrix = _viewMatrix;
    return ErrorCode::SUCCESS;
}

