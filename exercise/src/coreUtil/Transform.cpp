#include <cmath>
#include "Transform.h"
#include "Vector3f.h"
#include "Constants.h"
#include <assert.h>
using namespace Constants;
Transform::Transform(): _transRotTranDirty(true),
                        _viewDirty(true),
                        _projDirty(true),
                        _MVDirty(true),
                        _MVPDirty(true)
{
    _translateMatrix.SetIdentity();
    _rotateMatrix.SetIdentity();
    _modelMatrix.SetIdentity();
    _viewMatrix.SetIdentity();
    _modelViewMatrix.SetIdentity();
    _modelViewProjMatrix.SetIdentity();
}

void Transform::SetTranslate(float x, float y, float z)
{
    _transRotTranDirty = true;
    _translateMatrix.SetIdentity();
    _translateMatrix(1, 4) = x;
    _translateMatrix(2, 4) = y;
    _translateMatrix(3, 4) = z;
}

void Transform::SetArbitraryRotation(float angle, float axisX, float axisY, float axisZ)
{
    _transRotTranDirty = true;
    _rotateMatrix.SetIdentity();
    float radians, sine, cosine;
    Vector3f r(axisX, axisY, axisZ);
    r.Normalized();
    radians = angle * Math::PI / 180.0f;
    sine = sin(radians);
    cosine = cos(radians);
    float xy1MinusCos = r.x * r.y * (1 - cosine);
    float yz1MinusCos = r.y * r.z * (1 - cosine);
    float xz1MinusCos = r.x * r.z * (1 - cosine);

    _rotateMatrix(1, 1) = cosine + (1 - cosine) * r.x * r.x;
    _rotateMatrix(1, 2) = xy1MinusCos - r.z * sine;
    _rotateMatrix(1, 3) = xz1MinusCos + r.y * sine;

    _rotateMatrix(2, 1) = xy1MinusCos + r.z * sine;
    _rotateMatrix(2, 2) = cosine + (1 - cosine) * r.y * r.y;
    _rotateMatrix(2, 3) = yz1MinusCos - r.x * sine;

    _rotateMatrix(3, 1) = xz1MinusCos - r.y * sine;
    _rotateMatrix(3, 2) = yz1MinusCos + r.x * sine;
    _rotateMatrix(3, 3) = cosine + (1 - cosine) * r.z * r.z;

    _rotateMatrix(4, 4) = 1.0f;
}

void Transform::SetArbitraryRotation(float angle, Vector3f axis)
{
    SetArbitraryRotation(angle, axis.x, axis.y, axis.z);
}

void Transform::SetAxisAngles(float xDegree, float yDegree, float zDegree)
{
    Matrix4f xAxisRotation;
    xAxisRotation.SetIdentity();

}

void Transform::SetProjection(float fov, float aspectRatio, float zNear, float zFar)
{
    float radians = fov * Math::PI / 360.0f;
    float sine = sin(radians);

    float deltaZ = zFar - zNear;

    assert(fabs(deltaZ) > Math::EPSILON);
    assert(fabs(sine) > Math::EPSILON);

    float cotangent = cos(radians) / sine;
    _projectionMatrix(1, 1) = cotangent / aspectRatio;

    _projectionMatrix(2, 2) = cotangent;

    _projectionMatrix(3, 3) = -(zFar + zNear) / deltaZ;
    _projectionMatrix(3, 4) = -2 * zNear * zFar / deltaZ;

    _projectionMatrix(4, 3) = -1;
    _projDirty = true;
}

int Transform::GetModelMatrix(Matrix4f& result)
{
    if (_CanModelMatrixRead())
    {
        result = _modelMatrix;
        return ErrorCode::SUCCESS;
    }
    _modelMatrix = _translateMatrix.Mul(_rotateMatrix);
    result = _modelMatrix;
    _transRotTranDirty = false;
    return ErrorCode::SUCCESS;
}

void Transform::SetCamera(const Camera camera)
{
    _camera = camera;
    _camera.GetViewMatrix(_viewMatrix);
    _viewDirty = true;
}

int Transform::GetViewMatrix(Matrix4f& viewMatrix)
{
    viewMatrix = _viewMatrix;
    _viewDirty = false;
    return ErrorCode::SUCCESS;
}

int Transform::GetProjMatrix(Matrix4f& projMatrix)
{
    projMatrix = _projectionMatrix;
    _projDirty = false;
    return ErrorCode::SUCCESS;
}

int Transform::GetMVMatrix(Matrix4f& modelViewMatrix)
{
    if (_CanMVMatrixRead())
    {
        modelViewMatrix = _modelViewMatrix;
        return ErrorCode::SUCCESS;
    }
    if (!_CanModelMatrixRead())
    {
        GetModelMatrix(_modelMatrix);
    }
    if (!_CanViewMatrixRead())
    {
        GetViewMatrix(_viewMatrix);
    }
    _modelViewMatrix = _viewMatrix.Mul(_modelMatrix);
    modelViewMatrix = _modelViewMatrix;
    return ErrorCode::SUCCESS;
}

int Transform::GetMVPMatrix(Matrix4f& MVPMatrix)
{
    if (_CanMVPMatrixRead())
    {
        MVPMatrix = _modelViewProjMatrix;
        return ErrorCode::SUCCESS;
    }

    GetMVMatrix(_modelViewMatrix);
    GetProjMatrix(_projectionMatrix);
    _modelViewProjMatrix = _projectionMatrix.Mul(_modelViewMatrix);
    MVPMatrix = _modelViewProjMatrix;
    return ErrorCode::SUCCESS;
}

bool Transform::_CanModelMatrixRead()
{
    return !_transRotTranDirty;
}

bool Transform::_CanViewMatrixRead()
{
    return !_viewDirty;
}

bool Transform::_CanProjMatrixRead()
{
    return !_projDirty;
}

bool Transform::_CanMVMatrixRead()
{
    return _CanModelMatrixRead() && _CanViewMatrixRead();
}

bool Transform::_CanMVPMatrixRead()
{
    return  _CanModelMatrixRead() && _CanViewMatrixRead() && _CanProjMatrixRead();
}