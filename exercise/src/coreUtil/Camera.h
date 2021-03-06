#ifndef Camera_h__
#define Camera_h__
#include "Matrix.h"
#include "Vector3f.h"
class Camera
{
public:
    friend class Transform;
    Camera();
    Camera(const Vector3f& eyePos, const Vector3f& center, const Vector3f& up);
    void SetExtrinsicParams(const Vector3f& eyePos, const Vector3f& center, const Vector3f& up);
    int GetViewMatrix(Matrix4f& viewMatrix);
private:

    Matrix4f _viewMatrix;
};
#endif // Camera_h__
