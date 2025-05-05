#include <gtest/gtest.h>
#include "Point2D.h"

TEST(TestPoint2D, PrintToStdOut) {
    Point2D p1 {1, 2};
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    std::cout << p1;

    std::cout.rdbuf(old);

    EXPECT_EQ(buffer.str(), "(1, 2)");
}

TEST(TestPoint2D, DefaultConstructor) {
    Point2D p1;

    EXPECT_EQ(p1.zero.x, 0);
    EXPECT_EQ(p1.zero.y, 0);

    EXPECT_EQ(p1.left.x, -1);
    EXPECT_EQ(p1.left.y, 0);

    EXPECT_EQ(p1.right.x, 1);
    EXPECT_EQ(p1.right.y, 0);

    EXPECT_EQ(p1.up.x, 0);
    EXPECT_EQ(p1.up.y, 1);

    EXPECT_EQ(p1.down.x, 0);
    EXPECT_EQ(p1.down.y, -1);

    EXPECT_EQ(p1.x, 0);
    EXPECT_EQ(p1.y, 0);
}

TEST(TestPoint2D, ConstructFromPoint2D) {
    Point2D p1 {1, 1};
    Point2D p2(p1);

    EXPECT_EQ(p2.x, 1);
    EXPECT_EQ(p2.y, 1);
    EXPECT_NE(&p1, &p2);
}

TEST(TestPoint2D, ConstructFromPair) {
    std::pair<float, float> testPair {1.0f, 1.0f};
    Point2D p1(testPair);

    EXPECT_EQ(p1.x, 1);
    EXPECT_EQ(p1.y, 1);
}

TEST(TestPoint2D, ConstructFromVector) {
    std::vector<float> testVector {1.0f, 1.0f};
    Point2D p1(testVector);

    EXPECT_EQ(p1.x, 1);
    EXPECT_EQ(p1.y, 1);
}

TEST(TestPoint2D, Equals) {
    Point2D p1{1, 1};
    Point2D p2{1, 1};

    bool expected = true;
    bool actual = p1 == p2;

    EXPECT_EQ(expected, actual);
}

TEST(TestPoint2D, NotEquals) {
    Point2D p1{1, 1};
    Point2D p2{2, 2};

    bool expected = true;
    bool actual = p1 != p2;

    EXPECT_EQ(expected, actual);
}

TEST(TestPoint2D, Subtract) {
    Point2D p1{2, 2};
    Point2D p2{1, 1};

    float expected = 1;
    Point2D actual = p1 - p2;

    EXPECT_EQ(expected, actual.x);
    EXPECT_EQ(expected, actual.y);
}

TEST(TestPoint2D, Addition) {
    Point2D p1{1, 1};
    Point2D p2{1, 1};

    float expected = 2;
    Point2D actual = p1 + p2;

    EXPECT_EQ(expected, actual.x);
    EXPECT_EQ(expected, actual.y);
}

TEST(TestPoint2D, ScalarAndPoint2DMultiplication) {
    Point2D p1{1, 1};
    float scalar = 2;

    float expected = 2;
    Point2D actual = scalar * p1;

    EXPECT_EQ(expected, actual.x);
    EXPECT_EQ(expected, actual.y);
}

TEST(TestPoint2D, Point2DAndScalarMultiplication) {
    Point2D p1{1, 1};
    float scalar = 2;

    float expected = 2;
    Point2D actual = p1 * scalar;

    EXPECT_EQ(expected, actual.x);
    EXPECT_EQ(expected, actual.y);
}

TEST(TestPoint2D, Point2DAndScalarDivision) {
    Point2D p1{2, 2};
    float scalar = 2;

    float expected = 1;
    Point2D actual = p1 / scalar;

    EXPECT_EQ(expected, actual.x);
    EXPECT_EQ(expected, actual.y);
}
