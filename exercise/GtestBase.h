#ifndef GtestBase_h__
#define GtestBaes_h__
#include <gtest/gtest.h>
#include "Matrix.h"
#include "Vector3f.h"
#include "Constants.h"

class GtestBase : public testing::Test
{
protected:
    void virtual IsMatrixEqual(Matrix4f& lhv, Matrix4f& rhv)
    {
        for(int i = 1; i <= Matrix4f::DIM; i++)
        {
            for(int j = 1; j <= Matrix4f::DIM; j++)
            {
                EXPECT_FLOAT_EQ(lhv(i,j), rhv(i,j)) << "matrix x and y differ at (i, j) " << i<<" "<<j;
            }
        }
    }

    void virtual IsVectorEQ(const Vector4f& lhv, const Vector4f& rhv)
    {
        for(int i = 1; i <= Vector4f::DIM; i++)
        {
            EXPECT_NEAR(lhv[i], rhv[i], Constants::Math::EPSILON) << "Vectors x and y differ at index " << i;
        }
    }

    void virtual IsVectorEQ(Vector3f& lhv, Vector3f& rhv)
    {
        EXPECT_FLOAT_EQ(lhv.x, rhv.x);
        EXPECT_FLOAT_EQ(lhv.y, rhv.y);
        EXPECT_FLOAT_EQ(lhv.z, rhv.z);
    }
};
#endif