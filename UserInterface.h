#pragma once

#include "ArraySequence.h"
#include "LinkedListSequence.h"

ArraySequence<int>* ObjectCreatingArray();

LinkedListSequence<int>* ObjectCreatingLinkedList();

template<typename Type, typename T>
void Decomposition(T* object);

template<typename Type, typename T>
void Operations(T* object);

template<typename T>
void ObjectDeletion(T object);

template<typename T>
void UserInterfaceBase();

void UserInterface();