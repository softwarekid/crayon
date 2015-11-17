#ifndef Vector_h__
#define Vector_h__

/************************************************************************
 [] operator is designed in programming domain
************************************************************************/
class Vector4f
{
public:
    int static const DIM = 4;
    explicit Vector4f();
    Vector4f(float x, float y, float z, float w);
    Vector4f(const Vector4f& lsv);
    Vector4f operator - (const Vector4f& v);
    Vector4f operator * (float a);
    float& operator[] (int index);
    float operator[] (int index) const;
private:
    float _innerArray[DIM];
    void _SetZero();
};
#endif // Vector_h__