#include <iostream>
#include <string>
#include <cassert>
#include <vector>

#include "LinkedListSequence.h"

template<typename T>
LinkedListSequence<T>::LinkedListSequence(T* items, size_t count) {
    object = new LinkedList<T>(items, count);
}

template<typename T>
LinkedListSequence<T>::LinkedListSequence() {
    object = new LinkedList<T>();
}

template<typename T>
LinkedListSequence<T>::LinkedListSequence(LinkedList<T>* obj) { // Нужно для Concat (для этого надо перегрузить =)
    object = obj;
}

template<typename T>
LinkedListSequence<T>::LinkedListSequence(const LinkedListSequence<T>& other) {
    object = new LinkedList<T>(*other.object);
}

template<typename T>
LinkedListSequence<T>::LinkedListSequence(LinkedListSequence<T>&& other) {
    object = new LinkedList<T>(*other.object);
}

template<typename T>
bool LinkedListSequence<T>::operator <(const LinkedListSequence<T>& other) const { // лексикографическое сравнение
    for (size_t i = 0; i < std::min(object->GetLength(), other.object->GetLength()); i++) {
        if (object->Get(i) < other.object->Get(i)) {
            return true;
        }
        if (object->Get(i) > other.object->Get(i)) {
            return false;
        }
    }
    return object->GetLength() < other.object->GetLength();
}

template<typename T>
bool LinkedListSequence<T>::operator >(const LinkedListSequence<T>& other) const {
    return other < *this;
}

template<typename T>
bool LinkedListSequence<T>::operator ==(const LinkedListSequence<T>& other) const {
    return !(*this < other) && !(*this > other);
}

template<typename T>
bool LinkedListSequence<T>::operator !=(const LinkedListSequence<T>& other) const {
    return !(*this == other);
}

template<typename T>
bool LinkedListSequence<T>::operator <=(const LinkedListSequence<T>& other) const {
    return (*this < other || *this == other);
}

template<typename T>
bool LinkedListSequence<T>::operator >=(const LinkedListSequence<T>& other) const {
    return (*this > other || *this == other);
}

template<typename T>
T LinkedListSequence<T>::GetFirst() const {
    return object->GetFirst();
}

template<typename T>
T LinkedListSequence<T>::GetLast() const {
    return object->GetLast();
}

template<typename T>
T LinkedListSequence<T>::Get(int index) const {
    return object->Get(index);
}

template<typename T>
Sequence<T>* LinkedListSequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    Sequence<T>* res = dynamic_cast<Sequence<T>*>(new LinkedListSequence<T>(object->GetSubList(startIndex, endIndex)));
    return res;
}

template<typename T>
size_t LinkedListSequence<T>::GetLength() const {
    return object->GetLength();
}

template<typename T>
void LinkedListSequence<T>::Append(T item) {
    object->Append(item);
}

template<typename T>
void LinkedListSequence<T>::Prepend(T item) {
    object->Prepend(item);
}

template<typename T>
void LinkedListSequence<T>::InsertAt(T item, int index) {
    object->InsertAt(item, index);
}

template<typename T>
Sequence<T>* LinkedListSequence<T>::Concat(Sequence<T>* other) {
    LinkedList<T>* resObject = this->object->Concat(dynamic_cast<LinkedListSequence<T>*>(other)->object);
    LinkedListSequence<T>* res = new LinkedListSequence(resObject);
    return res;
}

template<typename T>
void LinkedListSequence<T>::Print(std::ostream& buff) const {
    object->Print(std::cout);
}

template<typename T>
LinkedListSequence<T>::~LinkedListSequence() {
    delete object;
}

template class LinkedListSequence<int>;
template class LinkedListSequence<double>;
template class LinkedListSequence<std::string>;
template class LinkedListSequence<char>;