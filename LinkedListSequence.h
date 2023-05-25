#pragma once

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
    LinkedListSequence(T* items, size_t count);
    LinkedListSequence();
    LinkedListSequence(LinkedList<T>* obj);
    LinkedListSequence(const LinkedListSequence<T>& other);
    LinkedListSequence(LinkedListSequence<T>&& other);

    bool operator <(const LinkedListSequence<T>& other) const;
    bool operator >(const LinkedListSequence<T>& other) const;
    bool operator ==(const LinkedListSequence<T>& other) const;
    bool operator !=(const LinkedListSequence<T>& other) const;
    bool operator <=(const LinkedListSequence<T>& other) const;
    bool operator >=(const LinkedListSequence<T>& other) const;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    size_t GetLength() const override;

    void Append(T item) override;
    void Prepend(T item) override;
    void InsertAt(T item, int index) override;
    Sequence<T>* Concat(Sequence<T>* other) override;

    void Print(std::ostream& buff) const override;

    ~LinkedListSequence() override;
};