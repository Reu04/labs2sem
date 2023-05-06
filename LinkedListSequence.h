#include <iostream>
#include <string>
#include <cassert>
#include <vector>

#include "Sequence.h"
#include "LinkedList.h"

template<typename T>
class LinkedListSequence : public Sequence<T> {
private:
    LinkedList<T>* object;
public:
    LinkedListSequence(T* items, size_t count) {
        object = new LinkedList<T>(items, count);
    }
    LinkedListSequence() {
        object = new LinkedList<T>();
    }
    LinkedListSequence(const LinkedListSequence<T>& other) {
        object = new LinkedList<T>(*other.object);
    }
    LinkedListSequence(LinkedListSequence<T>&& other) {
        object = new LinkedList<T>(*other.object);
    }

    bool operator <(const LinkedListSequence<T>& other) const { // лексикографическое сравнение
        for (size_t i = 0; i < std::min(object->GetSize(), other.object->GetSize()); i++) {
            if (object->Get(i) < other.object->Get(i)) {
                return true;
            }
            if (object->Get(i) > other.object->Get(i)) {
                return false;
            }
        }
        return object->GetSize() < other.object->GetSize();
    }
    bool operator >(const LinkedListSequence<T>& other) const {
        return other < *this;
    }
    bool operator ==(const LinkedListSequence<T>& other) const {
        return !(*this < other) && !(*this > other);
    }
    bool operator !=(const LinkedListSequence<T>& other) const {
        return !(*this == other);
    }
    bool operator <=(const LinkedListSequence<T>& other) const {
        return (*this < other || *this == other);
    }
    bool operator >=(const LinkedListSequence<T>& other) const {
        return (*this > other || *this == other);
    }

    T GetFirst() const override {
        return object->GetFirst();
    }
    T GetLast() const override {
        return object->GetLast();
    }
    T Get(int index) const override {
        return object->Get(index);
    }
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        Sequence<T>* res = object->GetSubList(startIndex, endIndex);
        return res;
    }
    size_t GetLength() const override {
        return object->GetLength();
    }

    void Append(T item) override {
        object->Append(item);
    }
    void Prepend(T item) override {
        object->Prepend(item);
    }
    void InsertAt(T item, int index) override {
        object->InsertAt(item, index);
    }
    Sequence<T>* Concat(Sequence<T>* other) override {
        // TODO
    }

    void Print(std::ostream& buff) const override {
        object->Print(std::cout);
    }

    ~LinkedListSequence() {
        delete object;
    }
};