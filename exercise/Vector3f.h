#ifndef Vector3f_h__
#define Vector3f_h__

/************************************************************************
 [] operator is designed in programming domain     
 x, y, z are used for math domain
************************************************************************/
struct Vector3f
{
public:
    int static const DIM = 3;
    Vector3f();
    Vector3f(float x, float y, float z);
    float operator[](int index);
    float operator[](int index) const;
    Vector3f operator * (float scalar);
    Vector3f operator - (const Vector3f v);
    Vector3f operator - (const Vector3f v) const;
    Vector3f operator + (const Vector3f v);
    Vector3f Cross(const Vector3f& v);
    float Dot(const Vector3f& v);
    float Length();
    float Length() const;
    void Normalized();

    float x,y,z;
};

#endif // Vector3f_h__
