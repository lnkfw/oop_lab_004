#pragma once
#include "figure.h"
#include <cmath>

template <Scalar T>
class Square : public Figure<T> {
public:
    Square() = default;

    Square(const Point<T>& center, T side, double angle_rad = 0.0) {
        T h = side / T(2);
        Point<T> local[4] = {
            Point<T>(-h, -h),
            Point<T>( h, -h),
            Point<T>( h,  h),
            Point<T>(-h,  h)
        };
        double ca = std::cos(angle_rad), sa = std::sin(angle_rad);
        for (int i = 0; i < 4; ++i) {
            double rx = double(local[i].x) * ca - double(local[i].y) * sa + double(center.x);
            double ry = double(local[i].x) * sa + double(local[i].y) * ca + double(center.y);
            this->add_vertex(Point<T>(static_cast<T>(rx), static_cast<T>(ry)));
        }
    }

    double area() const override {
        return this->polygon_area();
    }

    void print_info() const override {
        std::cout << "Квадрат: ";
        Figure<T>::print_info();
    }
};

template <Scalar T>
std::istream& operator>>(std::istream& is, Square<T>& s) {
    T cx, cy, side;
    double angle = 0.0;
    is >> cx >> cy >> side;
    if (!is.eof()) is >> angle;
    s = Square<T>(Point<T>(cx, cy), side, angle * M_PI / 180.0);
    return is;
}
