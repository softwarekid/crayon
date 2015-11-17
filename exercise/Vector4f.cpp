#include "Vector4f.h"
#include <string.h>
#include <assert.h>
#include <cmath>
#include "Constants.h"

Vector4f::Vector4f() 
{
    _SetZero();
}

Vector4f::Vector4f(const Vector4f& lsv)
{
    for (int i = 0; i < DIM; i++)
    {
        _innerArray[i] = lsv._innerArray[i];
    }
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
    assert(index >= 0 && index < DIM);
    return _innerArray[index];
}

float Vector4f::operator[](int index) const
{
    assert(index >= 0 && index < DIM);
    return _innerArray[index];
}

Vector4f Vector4f::operator-(const Vector4f& v)
{
    Vector4f result;
    for (int i = 0; i < DIM; i++)
    {
        result[i] = operator[](i) - v[i];
    }
    return result;
}

Vector4f Vector4f::operator*(float a)
{
    Vector4f result;
    for (int i = 0; i < DIM; i++)
    {
        result[i] = operator[](i) * a;
    }
    return result;
}
