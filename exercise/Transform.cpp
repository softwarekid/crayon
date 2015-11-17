#include <cmath>
#include "Transform.h"
#include "Vector3f.h"
#include "Constants.h"
#include <assert.h>
using namespace Constants;
Transform::Transform(): _transRotUpdated(false),
                        _modelCahed(false),
                        _viewCached(false),
                        _prjCached(false),
                        _MVCached(false),
                        _MVPCached(false)
{
}

void Transform::SetTranslate(float x, float y, float z)
{
    _transRotUpdated = true;
    _translateMatrix.SetIdentity();
    _translateMatrix(1, 4) = x;
    _translateMatrix(2, 4) = y;
    _translateMatrix(3, 4) = z;
}

void Transform::SetRotation(float angle, float axisX, float axisY, float axisZ)
{
    _transRotUpdated = true;
    float radians, sine, cosine, ab, bc, ca, tx, ty, tz;
    Vector3f r(axisX, axisY, axisZ);
    r.Normalized();
    radians = angle * Constants::Math::PI / 180.0f;
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
    _prjCached = true;
}

int Transform::GetModelMatrix(Matrix4f& result)
{
    if (_CanModelMatrixRead())
    {
        result = _modelMatrix;
        _transRotUpdated = false;
    }
    assert(_transRotUpdated);
    _modelMatrix = _translateMatrix.Mul(_rotateMatrix);
    _modelCahed = true;
    return ErrorCode::SUCCESS;
}

void Transform::SetCamera(const Camera camera)
{
    _camera = camera;
    _camera.GetViewMatrix(_viewMatrix);
    _viewCached = true;
}

int Transform::GetViewMatrix(Matrix4f& viewMatrix)
{
    assert(_viewCached);
    viewMatrix = _viewMatrix;
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
        _camera.GetViewMatrix(_viewMatrix);
    }
    _modelViewMatrix = _modelMatrix.Mul(_viewMatrix);
    _MVCached = true;
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
    _modelViewProjMatrix = _modelViewMatrix.Mul(_projectionMatrix);
    _MVPCached = true;
    MVPMatrix = _modelViewProjMatrix;
    return ErrorCode::SUCCESS;
}

bool Transform::_CanModelMatrixRead()
{
    return _modelCahed && !_transRotUpdated;
}

bool Transform::_CanViewMatrixRead()
{
    return _viewCached;
}

bool Transform::_CanMVMatrixRead()
{
    return _MVCached && _CanModelMatrixRead();
}

bool Transform::_CanMVPMatrixRead()
{
    return _MVPCached ;
}