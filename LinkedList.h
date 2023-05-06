#include <iostream>
#include <string>
#include <cassert>
#include <vector>

template<typename T>
struct Node {
    T data_;
    Node<T>* next_ = nullptr;
    Node<T>* prev_ = nullptr;
};
template<typename T>
class LinkedList {
private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;
public:
    class Iterator { // BidirectionalIterator
    private:
        friend class LinkedList<T>;
        Node<T>* curr_;
    public:
        Iterator(Node<T>* node) : curr_(std::move(node)) {}
        T& operator *() const {
            return curr_->data_;
        }
        Iterator& operator ++() {
            if (curr_->next_ == nullptr) {
                throw std::runtime_error("IndexOutOfRange");
            }
            curr_ = curr_->next_;
            return *this;
        }
        Iterator& operator --() {
            if (curr_->prev_ == nullptr) {
                throw std::runtime_error("IndexOutOfRange");
            }
            curr_ = curr_->prev_;
            return *this;
        }
        bool operator ==(const Iterator& rhs) const {
            return curr_ == rhs.curr_;
        }
        bool operator !=(const Iterator& rhs) const {
            return !(curr_ == rhs.curr_);
        }
    };

    LinkedList() : head_(new Node<T>()), tail_(new Node<T>()), size_(0) {};
    LinkedList(T* item, size_t count) : head_(new Node<T>()), tail_(new Node<T>()), size_(count) {
        Iterator it = begin();
        it.curr_->data_ = item[0];
        for (size_t i = 1; i < count; i++) {
            Node<T>* newNode = new Node<T>;
            it.curr_->next_ = newNode;
            newNode->prev_ = it.curr_;
            newNode->data_ = item[i];
            ++it;
        }
        it.curr_->next_ = tail_;
        tail_->prev_ = it.curr_;
    }
    LinkedList(const LinkedList& other) : head_(new Node<T>()), tail_(new Node<T>()), size_(other.size_) {
        Iterator it1 = begin();
        Iterator it2 = other.begin();
        it1.curr_->data_ = it2.curr_->data_;
        for (size_t i = 1; i < other.size_; i++) {
            ++it2;
            Node<T>* newNode = new Node<T>;
            it1.curr_->next_ = newNode;
            newNode->prev_ = it1.curr_;
            newNode->data_ = it2.curr_->data_;
            ++it1;
        }
        it1.curr_->next_ = tail_;
        tail_->prev_ = it1.curr_;
    }
    LinkedList(LinkedList&& other) : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0;
    }


    Iterator begin() const {
        return Iterator(head_);
    }
    Iterator end() const {
        return Iterator(tail_);
    }


    bool operator <(const LinkedList& other) const {
        Iterator it1 = begin();
        Iterator it2 = other.begin();
        for (size_t i = 0; i < std::min(size_, other.size_); i++) {
            if (it1.curr_->data_ < it2.curr_->data_) {
                return true;
            }
            if (it1.curr_->data_ > it2.curr_->data_) {
                return false;
            }
            ++it1;
            ++it2;
        }
        return GetLength() < other.GetLength();
    }
    bool operator >(const LinkedList& other) const {
        return other < *this;
    }
    bool operator ==(const LinkedList& other) const {
        return !(*this < other) && !(*this > other);
    }
    bool operator !=(const LinkedList& other) const {
        return !(*this == other);
    }
    bool operator <=(const LinkedList& other) const {
        return (*this < other || *this == other);
    }
    bool operator >=(const LinkedList& other) const {
        return (*this > other || *this == other);
    }


    T GetFirst() const {
        if (head_ == nullptr) {
            throw std::runtime_error("IndexOutOfRange");
        }
        return head_->data_;
    }
    T GetLast() const {
        if (tail_->prev_ == nullptr) {
            throw std::runtime_error("IndexOutOfRange");
        }
        return tail_->prev_->data_;
    }
    T Get(int index) const {
        Iterator it = begin();
        for (int i = 0; i < index; i++) {
            if (it.curr_ == nullptr || it.curr_->next_->next_ == nullptr ) {
                throw std::runtime_error("IndexOutOfRange");
            }
            ++it;
        }
        return it.curr_->data_;
    }
    LinkedList<T>* GetSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex < 0 || startIndex >= GetLength() || endIndex >= GetLength()) {
            throw std::runtime_error("IndexOutOfRange");
        }
        size_t size = endIndex - startIndex + 1;
        size_t index = 0;
        T* arr = new T[size];
        Iterator it = begin();
        for (int i = 0; i <= endIndex; i++) {
            if (i >= startIndex) {
                arr[index] = it.curr_->data_;
                index++;
            }
            ++it;
        }
        LinkedList<T>* res = new LinkedList<T>(arr, size);
        return res;
    }
    size_t GetLength() const {
        return size_;
    }


    void Append(const T& item) {
        Node<T>* newTail = new Node<T>;
        newTail->data_ = item;
        newTail->next_ = tail_;
        if (head_ == nullptr) {
            head_ = newTail;
            tail_->prev_ = newTail;
        } else {
            newTail->prev_ = tail_->prev_;
            tail_->prev_->next_ = newTail;
            tail_->prev_ = newTail;
        }
        size_++;
    }
    void Prepend(const T& item) {
        if (head_== nullptr) {
            Append(item);
            size_++;
            return;
        }
        Node<T>* newHead = new Node<T>();
        newHead->next_ = head_;
        newHead->data_ = item;
        head_->prev_ = newHead;
        head_ = newHead;
        size_++;
    }
    void InsertAt(T item, int index) {
        if (index < 0) {
            throw std::runtime_error("IndexOutOfRange");
        }
        Iterator it = begin();
        for (int i = 0; i < index; i++) {
            if (it.curr_->next_->next_ == nullptr) {
                throw std::runtime_error("IndexOutOfRange");
            }
            ++it;
        }
        Node<T>* newNode = new Node<T>;
        newNode->data_ = item;

        newNode->prev_ = it.curr_->prev_;
        (it.curr_->prev_)->next_ = newNode;

        newNode->next_ = it.curr_;
        it.curr_->prev_ = newNode;

        size_++;
    }

    void Insert(T item, Iterator it) {
        if (it == nullptr) {
            return;
        }
        if (it.curr_ == head_) { // push front
            if (head_== nullptr) {
                it.curr_->data_ = item;
                it.curr_->next_ = tail_;
                tail_->prev_ = it.curr_;
                head_ = it.curr_;
                size_++;
                return;
            }
            Node<T>* newNode = new Node<T>;
            newNode->data_ = item;
            newNode->next_ = head_;
            head_->prev_ = newNode;
            head_ = newNode;
            size_++;
        } else if (it.curr_ == tail_) { // push back
            Node<T>* newNode = new Node<T>;
            newNode->data_ = item;
            newNode->next_ = tail_;
            newNode->prev_ = tail_->prev_;
            tail_->prev_->next_ = newNode;
            tail_->prev_ = newNode;
            size_++;
        } else { // insert in the middle
            Node<T>* newNode = new Node<T>;
            newNode->data_ = item;
            newNode->prev_ = it.curr_->prev_;
            (it.curr_->prev_)->next_ = newNode;
            newNode->next_ = it.curr_;
            it.curr_->prev_ = newNode;
            size_++;
        }
    }
    LinkedList<T>* Concat(LinkedList<T>* other) {
        Iterator it2 = other->begin();
        for (size_t i = 0; i < other->size_; i++) {
            Append(it2.curr_->data_);
            ++it2;
        }
        return this;
    }

    // TODO убрать из структуры
    void Print(std::ostream& buff) const {
        Iterator it = begin();
        for (size_t i = 0; i < size_; i++) {
            buff << it.curr_->data_ << "\t";
            ++it;
        }
        buff << std::endl;
    }
};