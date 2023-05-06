#include <iostream>
#include <string>
#include <cassert>
#include <vector>

#include "Sequence.h"
#include "DynamicArray.h"

template<typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* object;
public:
    ArraySequence(T* items, size_t count) {
        object = new DynamicArray<T>(items, count);
    }
    ArraySequence(const DynamicArray<T>& obj) { // Нужно для Concat (для этого надо перегрузить =)
        *object = obj;
    }
    ArraySequence() {
        object = new DynamicArray<T>();
    }
    ArraySequence(const ArraySequence<T>& other) {
        object = new DynamicArray<T>(*other.object);
    }
    ArraySequence(ArraySequence<T>&& other) {
        object = new DynamicArray<T>(*other.object);
    }

    bool operator <(const ArraySequence<T>& other) const { // лексикографическое сравнение
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
    bool operator >(const ArraySequence<T>& other) const {
        return other < *this;
    }
    bool operator ==(const ArraySequence<T>& other) const {
        return !(*this < other) && !(*this > other);
    }
    bool operator !=(const ArraySequence<T>& other) const {
        return !(*this == other);
    }
    bool operator <=(const ArraySequence<T>& other) const {
        return (*this < other || *this == other);
    }
    bool operator >=(const ArraySequence<T>& other) const {
        return (*this > other || *this == other);
    }

    T GetFirst() const override {
        return object->Get(0);
    }
    T GetLast() const override {
        return object->Get(object->GetSize() - 1);
    }
    T Get(int index) const override {
        return object->Get(index);
    }
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex < 0 || startIndex > object->GetSize() || endIndex > object->GetSize()) {
            throw std::runtime_error("IndexOutOfRange");
        }
        size_t size = endIndex - startIndex + 1;
        T* arr = new T[size];
        size_t index = 0;
        for (size_t i = startIndex; i <= endIndex; i++) {
            arr[index] = object->Get(i);
            index++;
        }
        Sequence<T>* res = new ArraySequence(arr, size);
        return res;
    }
    size_t GetLength() const override {
        return object->GetSize();
    }

    void Append(T item) override {
        object->Set(object->GetSize(), item);
    }
    void Prepend(T item) override {
        object->Set(0, item);
    }
    void InsertAt(T item, int index) override {
        object->Set(index, item);
    }
    Sequence<T>* Concat(Sequence<T>* other) override {
        ArraySequence<T>* temp = new ArraySequence<T>(*dynamic_cast<ArraySequence<T>*>(other));
        T* arr = new T;
        size_t size = GetLength() + temp->GetLength();
        for (size_t i = 0; i < GetLength(); i++) {
            arr[i] = object->Get(i);
        }
        for (size_t i = 0; i < temp->GetLength(); i++) {
            arr[GetLength() + i] = temp->object->Get(i);
        }

        ArraySequence<T>* res = new ArraySequence<T>(arr, size);
        delete temp;
        return dynamic_cast<Sequence<T>*>(res);
    }

    void Print(std::ostream& buff) const override {
        object->Print(std::cout);
    }

    ~ArraySequence() {
        delete object;
    }
};
