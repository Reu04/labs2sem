#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

template<typename T>
class DynamicArray {
private:
    size_t size_;
    T* ptr_;
public:
    DynamicArray();
    DynamicArray(size_t size);
    DynamicArray(T* items, size_t size);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other);


    T Get(int index) const;
    size_t GetSize() const;


    void Resize(size_t newSize);
    void Set(int index, T value);


    DynamicArray<T>& operator=(const DynamicArray<T>& other);
    T& operator [](const size_t& index);
    T operator [](const size_t& index) const;
    DynamicArray& operator +(const DynamicArray& other);
    bool operator <(const DynamicArray& other) const;
    bool operator >(const DynamicArray& other) const;
    bool operator ==(const DynamicArray& other) const;
    bool operator !=(const DynamicArray& other) const;
    bool operator <=(const DynamicArray& other) const;
    bool operator >=(const DynamicArray& other) const;

    // TODO убрать из структуры
    void Print(std::ostream& buff) const;


    ~DynamicArray();
};