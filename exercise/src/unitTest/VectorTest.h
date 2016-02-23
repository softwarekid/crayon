#ifndef VectorTest_h__
#define VectorTest_h__


#include <cppunit/extensions/HelperMacros.h>
#include "Vector3f.h"
#include "Vector4f.h"

class VectorTest:public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(VectorTest);
    CPPUNIT_TEST(TestConstructor);
    CPPUNIT_TEST(TestAssign);
    CPPUNIT_TEST(TestMinus);
    CPPUNIT_TEST(TestMul);
    CPPUNIT_TEST(TestCross);
    CPPUNIT_TEST(TestDot);
    CPPUNIT_TEST(TestGetter);
    CPPUNIT_TEST(TestLength);
    CPPUNIT_TEST(TestNormalized);

    CPPUNIT_TEST_SUITE_END();
public:
    void setUp();
    void tearDown();
    void TestConstructor();
    void TestAssign();
    void TestMinus();
    void TestMul();
    void TestCross();
    void TestDot();
    void TestGetter();
    void TestLength();
    void TestNormalized();
private:
    bool _IsVectorEqual(const Vector4f& v1, const Vector4f& v2);
    bool _IsVectorEqual(const Vector3f& v1, const Vector3f& v2);
};

#endif // VectorTest_h__
