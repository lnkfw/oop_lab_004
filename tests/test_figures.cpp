#include <gtest/gtest.h>
#include "point.h"
#include "triangle.h"
#include "square.h"
#include "rectangle.h"
#include "array.h"

TEST(TriangleTest, AreaIsCorrect) {
    Triangle<double> t(Point<double>(0,0), Point<double>(4,0), Point<double>(0,3));
    EXPECT_NEAR((double)t, 6.0, 1e-6);
}

TEST(SquareTest, AreaIsCorrect) {
    Square<double> s(Point<double>(0,0), 2);
    EXPECT_NEAR((double)s, 4.0, 1e-6);
}

TEST(RectangleTest, AreaIsCorrect) {
    Rectangle<double> r(Point<double>(0,0), 3, 2);
    EXPECT_NEAR((double)r, 6.0, 1e-6);
}

TEST(TriangleTest, CenterIsCorrect) {
    Triangle<double> t(Point<double>(0,0), Point<double>(3,0), Point<double>(0,3));
    Point<double> c = t.center();
    EXPECT_NEAR(c.x, 1.0, 1e-6);
    EXPECT_NEAR(c.y, 1.0, 1e-6);
}

TEST(FigureTest, EqualityOperatorWorks) {
    Square<double> s1(Point<double>(0,0), 2);
    Square<double> s2(Point<double>(0,0), 2);
    EXPECT_TRUE(s1 == s2);
}

TEST(ArrayTest, RemoveElementReducesSize) {
    Array<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);
    arr.remove_at(1);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
}

TEST(ArrayTest, PushAndAccess) {
    Array<int> arr;
    arr.push_back(10);
    arr.push_back(20);
    EXPECT_EQ(arr.size(), 2);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
}
