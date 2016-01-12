#ifndef VectorGtest_h__
#define  VectorGtest_h__
class VectorGtest: public GtestBase
{
protected:
    virtual void SetUp()
    {
        v1.SetData(1, 2, 3, 4);
        v2.SetData(5, 6, 7, 8);
        v3.SetData(1, 1, 1, 1);
        v4.SetData(1, 2, 3);
        v5.SetData(2, 4, 5);
    }



    Vector4f v1;
    Vector4f v2;
    Vector4f v3;
    Vector4f result;

    Vector3f v4;
    Vector3f v5;
};

TEST_F(VectorGtest, Assign)
{
    v2 = v1;
    IsVectorEQ(v1, v2);
}

TEST_F(VectorGtest, Minus)
{
    result.SetData(4, 4, 4, 4);
    IsVectorEQ(result, v2 - v1);
}

TEST_F(VectorGtest, Mul)
{
    v1 = v1 * 2;
    result.SetData(2, 4, 6, 8);
    IsVectorEQ(result, v1);
}

TEST_F(VectorGtest, Cross)
{
    v4 = v4.Cross(v5);
    Vector3f result2(-2, 1, 0);
    IsVectorEQ(v4, result2);
}

TEST_F(VectorGtest, Dot)
{
    float r = v4.Dot(v5);
    EXPECT_FLOAT_EQ(25.0f, r);
}
TEST_F(VectorGtest, Length)
{
    v4.SetData(1, 2, 2);
    float r = v4.Length();
    EXPECT_FLOAT_EQ(3.0f, r);
}

TEST_F(VectorGtest, Normalized)
{
    v4.Normalized();
    float r = v4.Length();
    EXPECT_FLOAT_EQ(1.0f, r);
}
#endif