#ifndef Vector_h__
#define Vector_h__

/************************************************************************
 [] operator is designed in math domain
************************************************************************/
#include "Vector3f.h"
class Vector4f
{
public:
    int static const DIM = 4;
    explicit Vector4f();
    Vector4f(float * array);
    Vector4f(const Vector3f& vector3);
    Vector4f(float x, float y, float z, float w);
    Vector4f(const Vector4f& lsv);
    Vector4f& operator = (const Vector4f& v);
    Vector4f operator - (const Vector4f& v);
    Vector4f operator * (float a);
    float& operator[] (int index);
    float operator[] (int index) const;
    void SetData(float x, float y, float z, float w);
    void ReduceTo3DSpace();
    void GetInnerArray(float* value);
private:
    void _SetZero();
    float _innerArray[DIM];
};
#endif // Vector_h__