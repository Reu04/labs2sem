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
    explicit DynamicArray(size_t size) : size_(size) {
        ptr_ = new T[size];
    }
    DynamicArray(T* items, size_t size) : size_(size) {
        ptr_ = new T[size];
        for (size_t i = 0; i < size; i++) {
            ptr_[i] = items[i];
        }
    }
    DynamicArray(const DynamicArray& other) : size_(other.size_){
        ptr_ = new T[size_];
        for (size_t i = 0; i < other.size_; i++) {
            ptr_[i] = other.ptr_[i];
        }
    }
    DynamicArray(DynamicArray&& other) : size_(other.size_), ptr_(other.ptr_) {
        other.size_ = 0;
        other.ptr_ = nullptr;
    }


    T Get(int index) const {
        if (index >= (int) size_ || index < 0) {
            throw std::runtime_error("IndexOutOfRange");
        }
        return ptr_[index];
    }
    size_t GetSize() const {
        return size_;
    }


    void Resize(size_t newSize) {
        if (newSize == size_) {
            return;
        } else if (newSize > size_) {
            T* res = new T[newSize];
            for (size_t i = 0; i < size_; i++) {
                res[i] = ptr_[i];
            }
            delete[] ptr_;
            ptr_ = res;
            size_ = newSize;
        } else {
            T* res = new T[newSize];
            size_ = newSize;
            for (size_t i = 0; i < size_; i++) {
                res[i] = ptr_[i];
            }
            delete[] ptr_;
            ptr_ = res;
        }
    }
    void Set(int index, T value) {
        if (index > (int) size_ || index < 0) {
            throw std::runtime_error("IndexOutOfRange");
        } else if (index < (int) size_) {
            ptr_[index] = value;
        } else {
            Resize(size_ + 1);
            ptr_[index] = value;
        }
    }


    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        size_ = other.size_;
        if (ptr_ != nullptr) {
            delete[] ptr_;
        }
        ptr_ = new T[other.size_];
        for (size_t i = 0; i < other.size_; i++) {
            ptr_[i] = other.ptr_[i];
        }
        return *this;
    }
    T& operator [](const size_t& index) {
        return ptr_[index];
    }
    T operator [](const size_t& index) const { // получение для const DynamicArray<T> object
        return ptr_[index];
    }
    T& operator ->() {
        return *this;
    }
    DynamicArray& operator +(const DynamicArray& other) {
        size_t index = size_;
        for (size_t i = 0; i < other.size_; i++) {
            Set(index, other.Get(i));
        }
        return *this;
    }
    bool operator <(const DynamicArray& other) const { // лексикографическое сравнение
        for (size_t i = 0; i < std::min(size_, other.size_); i++) {
            if (ptr_[i] < other.ptr_[i]) {
                return true;
            }
            if (ptr_[i] > other.ptr_[i]) {
                return false;
            }
        }
        return GetSize() < other.GetSize();
    }
    bool operator >(const DynamicArray& other) const {
        return other < *this;
    }
    bool operator ==(const DynamicArray& other) const {
        return !(*this < other) && !(*this > other);
    }
    bool operator !=(const DynamicArray& other) const {
        return !(*this == other);
    }
    bool operator <=(const DynamicArray& other) const {
        return (*this < other || *this == other);
    }
    bool operator >=(const DynamicArray& other) const {
        return (*this > other || *this == other);
    }

    // TODO убрать из структуры
    void Print(std::ostream& buff) const {
        for (size_t i = 0; i < size_; i++) {
            buff << ptr_[i] << "\t";
        }
        buff << std::endl;
    }


    ~DynamicArray() {
        delete[] ptr_;
    }
};