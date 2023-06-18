#include "DynamicArray.h"
#include "LinkedList.h"
#include "Deque.h"

template<typename T>
DynamicArray<T>* ObjectCreatingDynamicArray() {
    std::cout << "Enter the number of items:\n";
    size_t num;
    std::cin >> num;
    if (num <= 0) {
        throw std::out_of_range("The number of items must be positive.");
    }

    T* items = new T[num];

    std::cout << "Enter the items:\n";
    for (size_t i = 0; i < num; i++) {
        T item;
        std::cin >> item;
        items[i] = item;
    }

    DynamicArray<T>* arr = new DynamicArray<T>(items, num);

    std::cout << "DynamicArray created.\n";
    std::cout << "DynamicArray: ";
    for (size_t i = 0; i < num; i++) {
        std::cout << arr->Get(i) << " ";
    }
    std::cout << std::endl;
    return arr;
}

template<typename T>
LinkedList<T>* ObjectCreatingLinkedList() {
    std::cout << "Enter the number of items:\n";
    size_t num;
    std::cin >> num;
    if (num <= 0) {
        throw std::out_of_range("The number of items must be positive.");
    }

    T* items = new T[num];

    std::cout << "Enter the items:\n";
    for (size_t i = 0; i < num; i++) {
        T item;
        std::cin >> item;
        items[i] = item;
    }

    LinkedList<T>* list = new LinkedList<T>(items, num);

    std::cout << "LinkedList created.\n";
    std::cout << "LinkedList: ";
    for (size_t i = 0; i < num; i++) {
        std::cout << list->Get(i) << " ";
    }
    std::cout << std::endl;
    return list;
}

template<typename T>
Deque<T>* ObjectCreatingDeque() {
    std::cout << "Enter the number of items:\n";
    size_t num;
    std::cin >> num;
    if (num <= 0) {
        throw std::out_of_range("The number of items must be positive.");
    }

    T* items = new T[num];

    std::cout << "Enter the items:\n";
    for (size_t i = 0; i < num; i++) {
        T item;
        std::cin >> item;
        items[i] = item;
    }

    Deque<T>* deque = new Deque<T>(num, items);

    std::cout << "Deque created.\n";
    std::cout << "Deque: ";
    deque->Print(std::cout);
    std::cout << std::endl;
    return deque;
}

template<typename T>
void ObjectDeletion(T object) {
    delete object;
    std::cout << "Object deleted.\n";
}

template<typename T>
void UIBase() {
    std::cout << "Enter the type of collection which you want to create:\n1. DynamicArray\n2. LinkedList\n3. Deque\n";
    int type;
    std::cin >> type;
    if (type == 1) {
        DynamicArray<T>* arr = ObjectCreatingDynamicArray<T>();

        std::cout << "If you want to continue: enter 0.\n";
        int exit;
        std::cin >> exit;

        while (exit == 0) {
            std::cout << "Which function do you want to use?\n1. Get\n2. GetSize\n3. Resize\n4. Set\n";
            int func;
            std::cin >> func;
            switch (func) {
                case 1:
                    std::cout << "Enter the index:\n";
                    size_t index;
                    std::cin >> index;
                    std::cout << "\nThe element: " << arr->Get(index) << std::endl;
                    break;
                case 2:
                    std::cout << "\nThe object size: " << arr->GetSize() << std::endl;
                    break;
                case 3:
                    std::cout << "Enter the new size:\n";
                    size_t size;
                    std::cin >> size;
                    arr->Resize(size);
                    std::cout << "Resized.\n";
                    break;
                case 4:
                    std::cout << "Enter the index:\n";
                    size_t index1;
                    std::cin >> index1;
                    std::cout << "Enter the new value:\n";
                    T value;
                    std::cin >> value;
                    arr->Set(index1, value);
                    std::cout << "Result: ";
                    arr->Print(std::cout);
                    std::cout << "Set.\n";
                    break;
                default:
                    std::cout << "Wrong function.\n";
                    break;
            }
            std::cout << "If you want to continue: enter 0.\n";
            std::cin >> exit;
        }
        ObjectDeletion(arr);
    } else if (type == 2) {
        LinkedList<T>* list = ObjectCreatingLinkedList<T>();

        std::cout << "If you want to continue: enter 0.\n";
        int exit;
        std::cin >> exit;

        while (exit == 0) {
            std::cout << "Which function do you want to use?\n1. GetFirst\n2. GetLast\n3. Get\n4. GetSubList\n5. GetLength\n6. Append\n7. Prepend\n8. InsertAt\n9. Concat\n";
            int func;
            std::cin >> func;
            switch (func) {
                case 1:
                    std::cout << "\nThe first element: " << list->GetFirst() << std::endl;
                    break;
                case 2:
                    std::cout << "\nThe last element: " << list->GetLast() << std::endl;
                    break;
                case 3:
                    std::cout << "Enter the index:\n";
                    size_t index;
                    std::cin >> index;
                    std::cout << "\nThe element: " << list->Get(index) << std::endl;
                    break;
                case 4:
                    std::cout << "Enter the start index:\n";
                    size_t start;
                    std::cin >> start;
                    std::cout << "Enter the end index:\n";
                    size_t end;
                    std::cin >> end;
                    std::cout << "\nThe sublist: ";
                    list->GetSubList(start, end)->Print(std::cout);
                    break;
                case 5:
                    std::cout << "\nThe length: " << list->GetLength() << std::endl;
                    break;
                case 6:
                    std::cout << "Enter the item:\n";
                    T item;
                    std::cin >> item;
                    list->Append(item);
                    std::cout << "Appended.\n";
                    list->Print(std::cout);
                    break;
                case 7:
                    std::cout << "Enter the item:\n";
                    std::cin >> item;
                    list->Prepend(item);
                    std::cout << "Prepended.\n";
                    list->Print(std::cout);
                    break;
                case 8:
                    std::cout << "Enter the item:\n";
                    std::cin >> item;
                    std::cout << "Enter the index:\n";
                    std::cin >> index;
                    list->InsertAt(item, index);
                    std::cout << "Inserted.\n";
                    list->Print(std::cout);
                    break;
                case 9: {
                    std::cout << "Enter the second list:\n";
                    LinkedList<T> *list2 = ObjectCreatingLinkedList<T>();
                    LinkedList<T> *res = list->Concat(list2);
                    std::cout << "Concatenated.\n";
                    res->Print(std::cout);
                    break;
                }
                default:
                    std::cout << "Wrong function.\n";
                    break;
            }
            std::cout << "If you want to continue: enter 0.\n";
            std::cin >> exit;
        }
        ObjectDeletion(list);
    } else if (type == 3) {
        Deque<T>* deque = ObjectCreatingDeque<T>();

        std::cout << "If you want to continue: enter 0.\n";
        int exit;
        std::cin >> exit;

        while (exit == 0) {
            std::cout << "Which function do you want to use?\n1. PushBack\n2. PushFront\n3. PopBack\n4. PopFront\n5. GetSize\n6. Empty\n7. Front\n8. Back\n9. Sort\n10. Concat\n11. GetSubsequence\n12. Find\n13. MergeFunc\n";
            int func;
            std::cin >> func;
            switch (func) {
                case 1:
                    std::cout << "Enter the item:\n";
                    T item;
                    std::cin >> item;
                    deque->PushBack(item);
                    std::cout << "Pushed back.\n";
                    deque->Print(std::cout);
                    break;
                case 2:
                    std::cout << "Enter the item:\n";
                    std::cin >> item;
                    deque->PushFront(item);
                    std::cout << "Pushed front.\n";
                    deque->Print(std::cout);
                    break;
                case 3:
                    deque->PopBack();
                    std::cout << "Popped back.\n";
                    deque->Print(std::cout);
                    break;
                case 4:
                    deque->PopFront();
                    std::cout << "Popped front.\n";
                    deque->Print(std::cout);
                    break;
                case 5:
                    std::cout << "\nThe size: " << deque->GetSize() << std::endl;
                    break;
                case 6:
                    if (deque->Empty()) {
                        std::cout << "\nEmpty.\n";
                    } else {
                        std::cout << "\nNot empty.\n";
                    }
                    break;
                case 7:
                    std::cout << "\nThe front element: " << deque->Front() << std::endl;
                    break;
                case 8:
                    std::cout << "\nThe back element: " << deque->Back() << std::endl;
                    break;
                case 9:
                    deque->Sort();
                    std::cout << "Sorted.\n";
                    deque->Print(std::cout);
                    break;
                case 10: {
                    std::cout << "Enter the second deque:\n";
                    Deque<T>* deque2 = ObjectCreatingDeque<T>();
                    Deque<T>* res = deque->Concat(deque2);
                    std::cout << "Concatenated.\n";
                    res->Print(std::cout);
                    break;
                }
                case 11:
                    std::cout << "Enter the start index:\n";
                    size_t start;
                    std::cin >> start;
                    std::cout << "Enter the end index:\n";
                    size_t end;
                    std::cin >> end;
                    std::cout << "\nThe subsequence: ";
                    deque->GetSubsequence(start, end)->Print(std::cout);
                    break;
                case 12:
                {
                    std::cout << "Enter the sub deque:\n";
                    Deque<T>* sub = ObjectCreatingDeque<T>();
                    if (deque->Find(sub)) {
                        std::cout << "Found.\n";
                    } else {
                        std::cout << "Not found.\n";
                    }
                    break;
                }
                case 13:
                {
                    std::cout << "Enter the second deque:\n";
                    Deque<T>* deque2 = ObjectCreatingDeque<T>();
                    deque->MergeFunc(deque2);
                    std::cout << "Merged.\n";
                    deque->Print(std::cout);
                    break;
                }
                default:
                    std::cout << "Wrong function.\n";
                    break;
            }
        }
    }
}

void UIforBaseCollections() {
    std::cout << "What type of elements will be in your collection?\n1. int\n2. double\n3. char\n";
    int type;
    std::cin >> type;
    switch (type) {
        case 1:
            UIBase<int>();
            break;
        case 2:
            UIBase<double>();
            break;
        case 3:
            UIBase<char>();
            break;
        default:
            std::cout << "Wrong type.\n";
            break;
    }
}