#ifndef MatrixGest_h__
#define MatrixGest_h__
#include "GtestBase.h"
class MatrixGtest : public GtestBase
{
protected:
    virtual void SetUp()
    {
        m1.SetIdentity();
        for(int i = 1; i <= Matrix4f::DIM; i++)
        {
            for(int j = 1; j <= Matrix4f::DIM; j++)
            {
                m2(i, j) = (i - 1) * 4 + j;
            }
        }
    }

    Matrix4f m1;
    Matrix4f m2;
    Matrix4f m3;
};

TEST_F(MatrixGtest, SetIndentity)
{
    EXPECT_EQ(1.0f, m1(1,1));
}

TEST_F(MatrixGtest, MultiplyMatrix)
{
    m1(1, 1) = 2;
    Matrix4f result = m1.Mul(m2);
    for(int i = 1; i <= Matrix4f::DIM; i++)
    {
        m2(1 ,i) = m2(1, i) * 2;
    }
}

TEST_F(MatrixGtest, Invert)
{
    m3.SetIdentity();
    m3(1, 1) = 2; m3(1, 2) = 1;
                  m3(2, 2) = 2;
                                m3(3, 3) = 2;
                                              m3(4, 4) = 1;
    Matrix4f result = m3.Invert();
    EXPECT_FLOAT_EQ(result(1, 1), 0.5f);
    EXPECT_FLOAT_EQ(result(1, 2), -0.25f);
    EXPECT_FLOAT_EQ(result(2, 2), 0.5f);
    EXPECT_FLOAT_EQ(result(3, 3), 0.5f);
    EXPECT_FLOAT_EQ(result(4, 4), 1.0f);
}

TEST_F(MatrixGtest, MultiplyVector)
{
    Vector4f v(1, 2, 3, 4);
    Vector4f result = m1.Mul(v);
    IsVectorEQ(result, v);
}
#endif
