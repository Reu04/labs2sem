#include "iostream"

//// Основная задача: учесть переход с конца массива на начало (кольцевой буфер) и наоборот !!!!1

template<typename T>
class Deque {
private:
    size_t size_;
    size_t capacity_;
    size_t start_; // first element position
    size_t end_; // after last element position
    T* data_;

    void Resize(size_t newCapacity) {
        if (capacity_ > newCapacity) {
            throw std::runtime_error("IndexOutOfRange");
        }
        capacity_ = newCapacity;
        T* newData = new T[capacity_];
        if (start_ > end_) {
            size_t firstPart = capacity_ - start_;
            std::copy(data_ + start_, data_ + capacity_, newData);
            std::copy(data_, data_ + end_, newData + firstPart);
        } else {
            std::copy(data_ + start_, data_ + end_, newData);
        }
        delete[] data_;
        data_ = newData;
        start_ = 0;
        end_ = size_;
    }
public:
    Deque() : data_(nullptr), size_(0), capacity_(2), start_(0), end_(0) { // bad alloc если пытаемся сразу выделить память
        data_ = new T[capacity_];
    }

    Deque(size_t size, T* data) : size_(size), capacity_(size_ + 2), start_(0), end_(size_) {
        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; +i++) {
            data_[i] = data[i];
        }
    }

    Deque(const Deque& other) : size_(other.size_), capacity_(other.capacity_), start_(0), end_(size_) {
        data_ = new T[other.capacity_];
        for (size_t i = 0; i < size_; +i++) {
            data_[i] = other.data_[i];
        }
    }

    Deque(Deque&& other) : size_(other.size_),
                           capacity_(other.capacity_),
                           start_(other.start_), end_(other.end_), data_(other.data_) {
        other.data_ = nullptr;
    }

    ~Deque() {
        delete[] data_;
    }

    friend class Iterator;
    class Iterator {
    private:
        T* Tstart_;
        size_t capacity_;
        const size_t& start_;
        const size_t& end_;
        int pos_;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;
        Iterator(T* Tstart, size_t capacity, const size_t& start, const size_t& end_, int pos):
                Tstart_(Tstart), capacity_(capacity), start_(start), end_(end_), pos_(pos) {}
        ~Iterator() = default;

        Iterator& operator ++() { // prefix
            *this->operator+=(1);
            return *this;
        }
        Iterator& operator --() { // prefix
            *this->operator-=(1);
            return *this;
        }
        Iterator& operator +=(difference_type n) {
            if (end_ < start_ && pos_ + n >= capacity_){
                pos_ = pos_ + n - capacity_;
            }
            else {
                pos_ = pos_ + n;
            }
            return *this;
        }
        Iterator operator +(difference_type n) {
            Iterator copy = *this;
            copy += n;
            return copy;
        }
        Iterator& operator -=(difference_type n) {
            if (pos_ - n < 0) {
                pos_ = pos_ - n + capacity_;
            }
            else {
                pos_ = pos_ - n;
            }
            return *this;
        }
        Iterator operator -(difference_type n) {
            Iterator copy = *this;
            copy -= n;
            return copy;
        }
        difference_type operator -(const Iterator& rhs) {
            size_t starttopos1;
            size_t starttopos2;
            if (pos_ >= start_) {
                starttopos1 = pos_ - start_;
            }
            else {
                starttopos1 = pos_ + capacity_ - start_;
            }
            if (rhs.pos_ >= start_) {
                starttopos2 = rhs.pos_ - start_;
            }
            else {
                starttopos2 = rhs.pos_ + capacity_ - start_;
            }
            return (int) (starttopos1 - starttopos2);
        }

        reference operator *() const {
            return *(Tstart_ + pos_);
        }
        Iterator& operator=(const Iterator& other) {
            this->pos_ = other.pos_;
            return *this;
        }
        pointer operator->() const {
            return Tstart_ + pos_;
        }

        bool operator ==(const Iterator& rhs) const {
            return (pos_ == rhs.pos_) && (start_ == rhs.start_) && (end_ == rhs.end_) && (capacity_ == rhs.capacity_)
                   && (Tstart_ == rhs.Tstart_);
        }
        bool operator !=(const Iterator& rhs) const {
            return !(*this == rhs);
        }
        bool operator <(const Iterator& rhs) const {
            size_t starttopos1;
            size_t starttopos2;
            if (pos_ >= start_) {
                starttopos1 = pos_ - start_;
            }
            else {
                starttopos1 = pos_ + capacity_ - start_;
            }
            if (rhs.pos_ >= start_) {
                starttopos2 = rhs.pos_ - start_;
            }
            else {
                starttopos2 = rhs.pos_ + capacity_ - start_;
            }
            return starttopos1 < starttopos2;
        }
        bool operator >(const Iterator& rhs) const {
            return !(*this < rhs) && !(*this == rhs);
        }
        bool operator <=(const Iterator& rhs) const {
            return *this < rhs || *this == rhs;
        }
        bool operator >=(const Iterator& rhs) const {
            return *this > rhs || *this == rhs;
        }
    };

    Iterator begin() const {
        return Iterator(data_, capacity_, start_, end_, start_);
    }

    Iterator end() const {
        return Iterator(data_, capacity_, start_, end_, end_);
    }

    void PushBack(T item) {
        if (size_ == capacity_) {
            Resize(static_cast<int>(size_ * 1.5) + 1);
        }
        if (capacity_ <= end_) { // т.к. проверили, что место есть: переход в начало массива (условное начало кольца)
            end_ = 0; // делаем шаг вперед
        }
        data_[end_] = item;
        end_++;
        size_++;
    }

    void PushFront(T item) {
        if (size_ >= capacity_ - 1) {
            Resize(static_cast<int>(size_ * 1.5) + 1);
        }
        if (start_ == 0) {
            start_ = capacity_; // делаем шаг назад
        }
        data_[--start_] = item;
        size_++;
    }

    void PopBack() {
        if (size_ == 0) {
            throw std::runtime_error("IndexOutOfRange");
        }
        if (end_ == 0) {
            end_ = capacity_;
        } else {
            end_--;
        }
        size_--;
    }

    void PopFront() {
        if (size_ == 0) {
            throw std::runtime_error("IndexOutOfRange");
        }
        if (start_ + 1 >= capacity_) {
            start_ = 0;
        } else {
            start_++;
        }
        size_--;
    }

    T& operator[](size_t index) const {
        if (index >= size_) {
            throw std::runtime_error("IndexOutOfRange");
        }
        if (start_ + index >= capacity_) {
            return data_[start_ + index - capacity_];
        }
        return data_[start_ + index];
    }

    bool operator <(const Deque<T>& other) const {
        auto i1 = this->begin();
        auto i2 = other.begin();
        while (i1 != this->end() || i2 != other.end()){
            if (*i1 > *i2) return false;
            i1++; i2++;
        }
        if (i1 != this->end() && i2 == other.end()) return false;
        return true;
    }

    bool operator ==(const Deque<T>& other) const {
        return !(*this < other) && !(*this > other);
    }

    size_t GetSize() const {
        return size_;
    }

    size_t GetCapacity() const { // for tests
        return capacity_;
    }

    T GetTest(size_t index) const { // for tests
        return data_[index];
    }

    bool Empty() const {
        return size_ == 0;
    }

    T& Front() const {
        return data_[start_];
    }

    T& Back() const {
        return data_[end_ - 1];
    }

    void Print(std::ostream &buff) {
        for (auto i = begin(); i != end(); ++i){
            std::cout << *i << " ";
        }
        std::cout << std::endl;
    }

    ////

    void Sort() {
        if (size_ == 0) {
            return;
        }
        std::sort(begin(), end());
    }

    Deque<T>* Map(T (*func)(T)) {
        Deque<T>* res = new Deque<T>;
        if (start_ <= end_) {
            for (size_t i = start_; i < end_; i++) {
                res->PushBack(func(data_[i]));
            }
        } else {
            for (size_t i = start_; i < capacity_; i++) {
                res->PushBack(func(data_[i]));
            }
            for (size_t i = 0; i < end_; i++) {
                res->PushBack(func(data_[i]));
            }
        }
        return res;
    }

    Deque<T>* Where(bool (*func)(T)) {
        Deque<T>* res = new Deque<T>;
        if (start_ <= end_) {
            for (size_t i = start_; i < end_; i++) {
                if (func(data_[i]) == true) {
                    res->PushBack(data_[i]);
                }
            }
        } else {
            for (size_t i = start_; i < capacity_; i++) {
                if (func(data_[i]) == true) {
                    res->PushBack(data_[i]);
                }
            }
            for (size_t i = 0; i < end_; i++) {
                if (func(data_[i]) == true) {
                    res->PushBack(data_[i]);
                }
            }
        }
        return res;
    }

    T Reduce(T (func)(T, T), T value) {
        T res = value;
        if (start_ <= end_) {
            for (size_t i = start_; i < end_; i++) {
                res = func(data_[i], res);
            }
        } else {
            for (size_t i = start_; i < capacity_; i++) {
                res = func(data_[i], res);
            }
            for (size_t i = 0; i < end_; i++) {
                res = func(data_[i], res);
            }
        }
        return res;
    }

    Deque<T>* Concat(Deque<T>* other) {
        Deque<T>* res = new Deque<T>;
        if (start_ < end_) {
            for (size_t i = start_; i < end_; i++) {
                res->PushBack(data_[i]);
            }
        } else {
            for (size_t i = start_; i < capacity_; i++) {
                res->PushBack(data_[i]);
            }
            for (size_t i = 0; i < end_; i++) {
                res->PushBack(data_[i]);
            }
        }
        if (other->start_ < other->end_) {
            for (size_t i = other->start_; i < other->end_; i++) {
                res->PushBack(other->data_[i]);
            }
        } else {
            for (size_t i = other->start_; i < other->capacity_; i++) {
                res->PushBack(other->data_[i]);
            }
            for (size_t i = 0; i < other->end_; i++) {
                res->PushBack(other->data_[i]);
            }
        }
        return res;
    }

    Deque<T>* GetSubsequence(size_t first, size_t second) { // second включительно
        if (first > second || second >= size_) {
            throw std::runtime_error("IndexOutOfRange");
        }
        Deque<T>* res = new Deque<T>;
        if (start_ < end_) {
            for (size_t i = first; i < second + 1; i++) {
                res->PushBack(data_[i]);
            }
        } else {
            for (size_t i = first; i < capacity_; i++) {
                res->PushBack(data_[i]);
            }
            for (size_t i = 0; i < second + 1; i++) {
                res->PushBack(data_[i]);
            }
        }
        return res;
    }

    bool Find(Deque<T>* other) const {
        if (other->size_ > size_) {
            return false;
        }
        auto it1 = begin();
        auto it2 = other->begin();
        int step = -1;
        while (it2 != other->end()) {
            if (it1 == end()) {
                return false;
            }
            if (*it1 == *it2) {
                it1 += 1;
                it2 += 1;
                step++;
            } else {
                it1 -= step;
                it2 = other->begin();
            }
        }
        return true;
    }

    bool FindElement(T value) const {
        for (auto it : *this) {
            if (it == value) {
                return true;
            }
        }
        return false;
    }

    Deque<T>* MergeFunc(Deque<T>* other) {
        Deque<T>* res = new Deque<T>;
        for (auto it1 : *this) {
            res->PushBack(it1);
        }
        for (auto it2 : *other) {
            if (res->FindElement(it2) == false) {
                res->PushBack(it2);
            }
        }
        return res;
    }
};

