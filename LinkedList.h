#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

template<typename T>
struct Node {
    T data_;
    Node<T>* next_;
    Node<T>* prev_;
};
template<typename T>
class LinkedList {
private:
    Node<T>* head_;
    Node<T>* tail_;
    size_t size_;
public:
    class Iterator {
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

    LinkedList();
    LinkedList(T* item, size_t count);
    LinkedList(const LinkedList& other);
    LinkedList(LinkedList&& other);


    Iterator begin() const {
        return Iterator(head_);
    }
    Iterator end() const {
        return Iterator(tail_);
    }

    bool operator <(const LinkedList& other) const;
    bool operator >(const LinkedList& other) const;
    bool operator ==(const LinkedList& other) const;
    bool operator !=(const LinkedList& other) const;
    bool operator <=(const LinkedList& other) const;
    bool operator >=(const LinkedList& other) const;


    T GetFirst() const;
    T GetLast() const;
    T Get(int index) const;
    LinkedList<T>* GetSubList(int startIndex, int endIndex) const;
    size_t GetLength() const;


    void Append(const T& item);
    void Prepend(const T& item);
    void InsertAt(T item, int index);

    void Insert(T item, Iterator it);
    LinkedList<T>* Concat(LinkedList<T>* other);

    // TODO убрать из структуры
    void Print(std::ostream& buff) const;

    ~LinkedList();
};