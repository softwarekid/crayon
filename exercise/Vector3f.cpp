#include <cmath>
#include <assert.h>
#include "Vector3f.h"
#include "Constants.h"

Vector3f::Vector3f(float x_, float y_, float z_)
{
    x = x_, y = y_, z = z_;
}

Vector3f::Vector3f()
{
    x = y = z = 0;
}

Vector3f Vector3f::Cross(const Vector3f& v)
{
    return Vector3f(y * v.z - z * v.y, 
                    z * v.x - x * v.z,
                    x * v.y - y * v.x);
}

float Vector3f::Dot(const Vector3f& v)
{
    return x * v.x + y * v.y + z * v.z;
}

float Vector3f::Length()
{
    return sqrt(x * x + y * y + z * z);
}

float Vector3f::Length() const
{
    return sqrt(x * x + y * y + z * z);
}

void Vector3f::Normalized()
{
    float length = Length();
    if (fabs(length) < Constants::Math::EPSILON)
    {
        return ;
    }
    x /= length;
    y /= length;
    z /= length;
}

float Vector3f::operator[](int index)
{
    assert(index >= 0 && index < DIM);
    switch(index)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    }
    return Constants::Math::FLOATMAX;
}

float Vector3f::operator[](int index) const
{
    assert(index >= 0 && index < DIM);
    switch(index)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    }
    return Constants::Math::FLOATMAX;
}

Vector3f Vector3f::operator*(float scalar)
{
    return Vector3f(x * scalar, y * scalar , z * scalar);
}

Vector3f Vector3f::operator-(const Vector3f v)
{
    return Vector3f(x - v.x, y - v.y, z - v.z);
}

Vector3f Vector3f::operator-(const Vector3f v) const
{
    return Vector3f(x - v.x, y - v.y, z - v.z);
}

Vector3f Vector3f::operator+(const Vector3f v)
{
    return Vector3f(x + v.x, y + v.y, z + v.z);
}

