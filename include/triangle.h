#pragma once
#include "figure.h"
#include <cmath>

template <Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() = default;

    Triangle(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
        this->add_vertex(a);
        this->add_vertex(b);
        this->add_vertex(c);
    }

    double area() const override {
        return this->polygon_area();
    }

    void print_info() const override {
        std::cout << "Треугольник: ";
        Figure<T>::print_info();
    }
};

template <Scalar T>
std::istream& operator>>(std::istream& is, Triangle<T>& t) {
    T x1, y1, x2, y2, x3, y3;
    is >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    t = Triangle<T>(Point<T>(x1, y1), Point<T>(x2, y2), Point<T>(x3, y3));
    return is;
}
