#pragma once
#include "figure.h"
#include <cmath>

template <Scalar T>
class Rectangle : public Figure<T> {
public:
    Rectangle() = default;

    Rectangle(const Point<T>& center, T width, T height, double angle_rad = 0.0) {
        T hw = width / T(2);
        T hh = height / T(2);
        Point<T> local[4] = {
            Point<T>(-hw, -hh),
            Point<T>( hw, -hh),
            Point<T>( hw,  hh),
            Point<T>(-hw,  hh)
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
        std::cout << "Прямоугольник: ";
        Figure<T>::print_info();
    }
};

template <Scalar T>
std::istream& operator>>(std::istream& is, Rectangle<T>& r) {
    T cx, cy, width, height;
    double angle = 0.0;
    is >> cx >> cy >> width >> height;
    if (!is.eof()) is >> angle;
    r = Rectangle<T>(Point<T>(cx, cy), width, height, angle * M_PI / 180.0);
    return is;
}
