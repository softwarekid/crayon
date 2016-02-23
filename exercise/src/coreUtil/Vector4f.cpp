#include "Vector4f.h"
#include <string.h>
#include <assert.h>
#include <cmath>
#include "Constants.h"

Vector4f::Vector4f() 
{
    _SetZero();
}

Vector4f::Vector4f(const Vector4f& lhs)
{
    for (int i = 0; i < DIM; i++)
    {
        _innerArray[i] = lhs._innerArray[i];
    }
}

Vector4f& Vector4f::operator=(const Vector4f& v)
{
    for(int i = 0; i < DIM; i++)
    {
        _innerArray[i] = v._innerArray[i];
    }
    return *this;
}

Vector4f::Vector4f(float* array)
{
    _innerArray[0] = array[0], _innerArray[1] = array[1], _innerArray[2] = array[2], _innerArray[3] = array[3];
}

Vector4f::Vector4f(const Vector3f& vector3)
{
    _innerArray[0] = vector3.x;
    _innerArray[1] = vector3.y;
    _innerArray[2] = vector3.z;
    _innerArray[3] = 1;
}

Vector4f::Vector4f(float x, float y, float z, float w)
{
    _innerArray[0] = x, _innerArray[1] = y, _innerArray[2] = z, _innerArray[3] = w;
}

void Vector4f::_SetZero()
{
    memset(_innerArray, 0, sizeof(float) * DIM);
}

float& Vector4f::operator[](int index)
{
    assert(index > 0 && index <= DIM);
    return _innerArray[index - 1];
}

float Vector4f::operator[](int index) const
{
    assert(index > 0 && index <= DIM);
    return _innerArray[index - 1];
}

void Vector4f::ReduceTo3DSpace()
{
    if (fabs(_innerArray[DIM - 1]) > Constants::Math::EPSILON)
    {
        for(int i = 0; i < DIM; i++)
        {
            _innerArray[i] = _innerArray[i] / _innerArray[DIM - 1];
        }
    }
}

void Vector4f::GetInnerArray(float* value)
{
    for(int i = 0; i < DIM; i++)
    {
        value[i] = _innerArray[i];
    }
}

Vector4f Vector4f::operator-(const Vector4f& v)
{
    Vector4f result;
    for (int i = 1; i <= DIM; i++)
    {
        result[i] = operator[](i) - v[i];
    }
    return result;
}

Vector4f Vector4f::operator*(float a)
{
    Vector4f result;
    for (int i = 1; i <= DIM; i++)
    {
        result[i] = operator[](i) * a;
    }
    return result;
}

void Vector4f::SetData(float x, float y, float z, float w)
{
    _innerArray[0] = x, _innerArray[1] = y, _innerArray[2] = z, _innerArray[3] = w;
}