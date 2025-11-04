#pragma once
#include "point.h"
#include <memory>
#include <cmath>
#include <iomanip>
#include <iostream>


template <Scalar T>
class Figure {
public:
    using PointPtr = std::unique_ptr<Point<T>>;

    Figure() : verts_(nullptr), size_(0), capacity_(0) {}
    virtual ~Figure() {
        clear_vertices();
    }

    Figure(const Figure& other) : verts_(nullptr), size_(0), capacity_(0) {
        if (other.size_ > 0) {
            reserve_vertices(other.size_);
            for (size_t i = 0; i < other.size_; ++i) {
                add_vertex(*(other.verts_[i]));
            }
        }
    }

    Figure(Figure&& other) noexcept
        : verts_(std::move(other.verts_)), size_(other.size_), capacity_(other.capacity_) {
        other.verts_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Figure& operator=(const Figure& other) {
        if (this == &other) return *this;
        clear_vertices();
        if (other.size_ > 0) {
            reserve_vertices(other.size_);
            for (size_t i = 0; i < other.size_; ++i) add_vertex(*(other.verts_[i]));
        }
        return *this;
    }

    Figure& operator=(Figure&& other) noexcept {
        if (this == &other) return *this;
        clear_vertices();
        verts_ = std::move(other.verts_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.verts_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        return *this;
    }

    void add_vertex(const Point<T>& p) {
        if (size_ >= capacity_) {
            size_t newcap = (capacity_ == 0) ? 4 : capacity_ * 2;
            reserve_vertices(newcap);
        }
        verts_[size_] = std::make_unique<Point<T>>(p);
        ++size_;
    }

    size_t vertex_count() const { return size_; }

    const Point<T>& vertex_at(size_t idx) const {
        return *(verts_[idx]);
    }

    Point<T> center() const {
        if (size_ == 0) return Point<T>();
        double sx = 0.0, sy = 0.0;
        for (size_t i = 0; i < size_; ++i) {
            sx += double(verts_[i]->x);
            sy += double(verts_[i]->y);
        }
        double n = double(size_);
        return Point<T>( static_cast<T>(sx / n), static_cast<T>(sy / n) );
    }

    virtual double area() const = 0;

    virtual void print_info() const {
        std::cout << "Центр: ";
        center().print();
        std::cout << "  Вершины: ";
        for (size_t i = 0; i < size_; ++i) {
            verts_[i]->print();
            std::cout << " ";
        }
        std::cout << "  Площадь: " << std::fixed << std::setprecision(4) << area();
    }

    explicit operator double() const { return area(); }

    bool operator==(const Figure& other) const { return std::fabs(area() - other.area()) < 1e-9; }
    bool operator!=(const Figure& other) const { return !(*this == other); }
    bool operator<(const Figure& other) const { return area() < other.area(); }
    bool operator>(const Figure& other) const { return area() > other.area(); }

protected:
    std::unique_ptr<PointPtr[]> verts_;
    size_t size_;
    size_t capacity_;

    void reserve_vertices(size_t newcap) {
        if (newcap <= capacity_) return;
        std::unique_ptr<PointPtr[]> newarr(new PointPtr[newcap]);
        for (size_t i = 0; i < size_; ++i) {
            newarr[i] = std::move(verts_[i]);
        }
        verts_.swap(newarr);
        capacity_ = newcap;
    }

    void clear_vertices() {
        verts_.reset();
        size_ = 0;
        capacity_ = 0;
    }

    double polygon_area() const {
        if (size_ < 3) return 0.0;
        double sum = 0.0;
        for (size_t i = 0; i < size_; ++i) {
            const Point<T>& p1 = *(verts_[i]);
            const Point<T>& p2 = *(verts_[(i + 1) % size_]);
            sum += double(p1.x) * double(p2.y) - double(p2.x) * double(p1.y);
        }
        return std::fabs(sum) / 2.0;
    }
};

template <Scalar T>
std::ostream& operator<<(std::ostream& os, const Figure<T>& f) {
    f.print_info();
    return os;
}
