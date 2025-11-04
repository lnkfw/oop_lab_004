#pragma once
#include <concepts>
#include <iostream>
#include <cmath>

template<typename T>
concept Scalar = std::integral<T> || std::floating_point<T>;

template <Scalar T>
class Point {
public:
    T x;
    T y;

    Point() : x(T(0)), y(T(0)) {}
    Point(T x_, T y_) : x(x_), y(y_) {}
    Point(const Point& other) : x(other.x), y(other.y) {}
    Point(Point&& other) noexcept : x(other.x), y(other.y) {}

    Point& operator=(const Point& other) {
        if (this != &other) { x = other.x; y = other.y; }
        return *this;
    }

    Point& operator=(Point&& other) noexcept {
        if (this != &other) { x = other.x; y = other.y; }
        return *this;
    }

    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
    Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
    Point operator*(T s) const { return Point(x * s, y * s); }

    double distance_to(const Point& o) const {
        double dx = double(x) - double(o.x);
        double dy = double(y) - double(o.y);
        return std::sqrt(dx*dx + dy*dy);
    }

    void print() const {
        std::cout << "(" << x << ", " << y << ")";
    }
};
