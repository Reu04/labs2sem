#include "UserInterface.h"

template<typename T>
ArraySequence<T>* ObjectCreatingArray() {
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

    ArraySequence<T>* arr = new ArraySequence<T>(items, num);

    std::cout << "ArraySequence created.\n";
    std::cout << "ArraySequence: ";
    for (size_t i = 0; i < num; i++) {
        std::cout << arr->Get(i) << " ";
    }
    std::cout << std::endl;
    return arr;
}

template<typename T>
LinkedListSequence<T>* ObjectCreatingLinkedList() {
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

    LinkedListSequence<T>* list = new LinkedListSequence<T>(items, num);

    std::cout << "LinkedListSequence created.\n";
    std::cout << "LinkedListSequence: ";
    for (size_t i = 0; i < num; i++) {
        std::cout << list->Get(i) << " ";
    }
    std::cout << std::endl;
    return list;
}

template<typename Type, typename T>
void Decomposition(Type* object) {
    std::cout << "Which function do you want to use?\n1. GetSubsequence\n2. GetLength\n3. GetFirst\n4. GetLast\n5. Get\n";
    int func;
    std::cin >> func;
    switch (func) {
        case 1:
            std::cout << "Enter the start and end indexes:\n";
            int start, end;
            std::cin >> start >> end;
            try {
                Sequence<T>* sub = dynamic_cast<Sequence<T>*>(object)->GetSubsequence(start, end);
                std::cout << "Subsequence: ";
                for (size_t i = 0; i < sub->GetLength(); i++) {
                    std::cout << sub->Get(i) << " ";
                }
                std::cout << "\n";
                delete sub;
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
            break;
        case 2:
            std::cout << "Length: " << object->GetLength() << "\n";
            break;
        case 3:
            std::cout << "First item: " << object->GetFirst() << "\n";
            break;
        case 4:
            std::cout << "Last item: " << object->GetLast() << "\n";
            break;
        case 5:
            std::cout << "Enter the index:\n";
            int index;
            std::cin >> index;
            try {
                std::cout << "Item: " << object->Get(index) << "\n";
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
            break;
        default:
            std::cout << "Wrong function\n";
            break;
    }
}

template<typename Type, typename T>
void Operations(Type* object) {
    std::cout << "Which function do you want to use?\n1. Append\n2. Prepend\n3. InsertAt\n4. Concat\n";
    int func;
    std::cin >> func;
    switch (func) {
        case 1:
            std::cout << "Enter the item:\n";
            T item;
            std::cin >> item;
            object->Append(item);
            std::cout << "Elements: ";
            for (size_t i = 0; i < object->GetLength(); i++) {
                std::cout << object->Get(i) << " ";
            }
            std::cout << "\n";
            break;
        case 2:
            std::cout << "Enter the item:\n";
            std::cin >> item;
            object->Prepend(item);
            std::cout << "Elements: ";
            for (size_t i = 0; i < object->GetLength(); i++) {
                std::cout << object->Get(i) << " ";
            }
            std::cout << "\n";
            break;
        case 3:
            std::cout << "Enter the item and index:\n";
            int index;
            std::cin >> item >> index;
            try {
                object->InsertAt(item, index);
                std::cout << "Elements: ";
                for (size_t i = 0; i < object->GetLength(); i++) {
                    std::cout << object->Get(i) << " ";
                }
                std::cout << "\n";
            }
            catch (std::runtime_error& e) {
                std::cout << e.what() << "\n";
            }
            break;
        case 4:
            std::cout << "Enter the type your sequence:\n1. ArraySequence\n2. LinkedListSequence\n";
            int type;
            std::cin >> type;
            if (type == 1) {
                ArraySequence<T>* arr = ObjectCreatingArray<T>();
                Sequence<T>* conc = object->Concat(arr);
                std::cout << "Concatenation: ";
                for (size_t i = 0; i < conc->GetLength(); i++) {
                    std::cout << conc->Get(i) << " ";
                }
                std::cout << "\n";
                delete arr;
                delete conc;
            }
            else if (type == 2) {
                Sequence<T>* list = dynamic_cast<Sequence<T>*>(ObjectCreatingLinkedList<T>());
                Sequence<T>* conc = object->Concat(list);
                std::cout << "Concatenation: ";
                for (size_t i = 0; i < conc->GetLength(); i++) {
                    std::cout << conc->Get(i) << " ";
                }
                std::cout << "\n";
                delete list;
                delete conc;
            }
            else {
                std::cout << "Wrong type.\n";
            }
            break;
        default:
            std::cout << "Wrong function.\n";
            break;
    }
}

template<typename T>
void ObjectDeletion(T object) {
    delete object;
    std::cout << "Object deleted.\n";
}

template<typename T>
void UserInterfaceBase() {
    std::cout << "Enter the type of sequence which you want to create:\n1. ArraySequence\n2. LinkedListSequence\n";
    int type;
    std::cin >> type;
    if (type == 1) {
        ArraySequence<T>* arr = ObjectCreatingArray<T>();

        std::cout << "If you want to continue: enter 0.\n";
        int exit;
        std::cin >> exit;

        while (exit == 0) {
            std::cout << "Which function do you want to use?\n1. Decomposition\n2. Operations\n";
            int func;
            std::cin >> func;
            switch (func) {
                case 1:
                    Decomposition<ArraySequence<T>, T>(arr);
                    break;
                case 2:
                    Operations<ArraySequence<T>, T>(arr);
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
        LinkedListSequence<T>* list = ObjectCreatingLinkedList<T>();
        std::cout << "If you want to continue: enter 0.\n";
        int exit;
        std::cin >> exit;

        while (exit == 0) {
            std::cout << "Which function do you want to use?\n1. Decomposition\n2. Operations\n";
            int func;
            std::cin >> func;
            switch (func) {
                case 1:
                    Decomposition<LinkedListSequence<T>, T>(list);
                    break;
                case 2:
                    Operations<LinkedListSequence<T>, T>(list);
                    break;
                default:
                    std::cout << "Wrong function.\n";
                    break;
            }
            std::cout << "If you want to continue: enter 0.\n";
            std::cin >> exit;
        }
        ObjectDeletion(list);
    } else {
        std::cout << "Wrong type.\n";
    }
}

void UserInterface() {
    std::cout << "What type of elements will be in your sequence?\n1. int\n2. double\n3. char\n";
    int type;
    std::cin >> type;
    switch (type) {
        case 1:
            UserInterfaceBase<int>();
            break;
        case 2:
            UserInterfaceBase<double>();
            break;
        case 3:
            UserInterfaceBase<char>();
            break;
        default:
            std::cout << "Wrong type.\n";
            break;
    }
}