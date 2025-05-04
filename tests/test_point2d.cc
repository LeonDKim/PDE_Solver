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
