#pragma once
#include <memory>
#include <utility>
#include <stdexcept>
#include <iostream>

// реализую вектор вручную, так как еще не проходили контейнеры

template <typename T>
class Array {
public:
    Array(size_t capacity = 4) : size_(0), capacity_(0), data_(nullptr) {
        if (capacity == 0) capacity = 1;
        reserve(capacity);
    }

    ~Array() = default;

    Array(const Array& other) : size_(other.size_), capacity_(other.capacity_) {
        data_ = std::unique_ptr<T[]>(new T[capacity_]);
        for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
    }

    Array(Array&& other) noexcept
        : size_(other.size_), capacity_(other.capacity_), data_(std::move(other.data_)) {
        other.size_ = 0; other.capacity_ = 0;
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;
        data_ = std::unique_ptr<T[]>(new T[other.capacity_]);
        capacity_ = other.capacity_;
        size_ = other.size_;
        for (size_t i = 0; i < size_; ++i) data_[i] = other.data_[i];
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this == &other) return *this;
        data_ = std::move(other.data_);
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.size_ = 0; other.capacity_ = 0;
        return *this;
    }

    void push_back(const T& v) {
        if (size_ >= capacity_) reserve(capacity_ * 2);
        data_[size_] = v;
        ++size_;
    }

    void push_back(T&& v) {
        if (size_ >= capacity_) reserve(capacity_ * 2);
        data_[size_] = std::move(v);
        ++size_;
    }

    void remove_at(size_t idx) {
        if (idx >= size_) throw std::out_of_range("remove_at: index out of range");
        for (size_t i = idx; i + 1 < size_; ++i) data_[i] = std::move(data_[i+1]);
        --size_;
    }

    T& operator[](size_t idx) {
        if (idx >= size_) throw std::out_of_range("operator[]: index out of range");
        return data_[idx];
    }

    const T& operator[](size_t idx) const {
        if (idx >= size_) throw std::out_of_range("operator[]: index out of range");
        return data_[idx];
    }

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }

    void reserve(size_t newcap) {
        if (newcap <= capacity_) return;
        std::unique_ptr<T[]> newdata(new T[newcap]);
        for (size_t i = 0; i < size_; ++i) newdata[i] = std::move(data_[i]);
        data_.swap(newdata);
        capacity_ = newcap;
    }

private:
    size_t size_;
    size_t capacity_;
    std::unique_ptr<T[]> data_;
};
