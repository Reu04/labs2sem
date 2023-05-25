#include "iostream"

template<typename T>
class Deque {
private:
    size_t size_;
    size_t capacity_;
    size_t start_; // first element position
    size_t end_; // last element position
    T* data_;

    void Resize(size_t newCapacity) {
        
    }
public:
    Deque() : data_(nullptr), size_(0), capacity_(2), start_(0), end_(0) { // bad alloc если пытаемся сразу выделить память
        data_ = new T[capacity_];
    }

    Deque(size_t size, T* data) : size_(size), capacity_(size_ * 2), start_(0), end_(size_ - 1) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; +i++) {
            data_[i] = data[i];
        }
    }

    Deque(const Deque& other) : size_(other.size_), capacity_(other.capacity_), start_(0), end_(size_ - 1) {
        data_ = new T[other.capacity_];
        for (size_t i = 0; i < size_; +i++) {
            data_[i] = other.data_[i];
        }
    }

    Deque(Deque&& other) : size_(std::move(other.size_)),
                           capacity_(std::move(capacity_)),
                           start_(std::move(other.start_)),end_(std::move(other.end_)), data_(std::move(other.data_)) {}

    ~Deque() {
        delete[] data_;
    }

    void PushBack(T item) {

    }
};