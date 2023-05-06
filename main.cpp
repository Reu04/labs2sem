//// Для реализации необходимо использовать возможности ООП и шаблонов C++
/// Для реализации используется инкапсуляция DynamicArray и делегирование ему большей части работы.

//// Все реализованные классы и основные алгоритмы необходимо покрыть (модульными) тестами.
/// Реализацию следует оснастить пользовательским интерфейсом (консольным) для проверки корректности реализации.

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

#include "DynamicArray.h"
#include "LinkedList.h"
#include "Sequence.h"
#include "ArraySequence.h"
#include "LinkedListSequence.h"

void TestDynamicArray() {
    std::cout << "\n\tTest Dynamic Array:\t\n";

    size_t size1 = 5, size2 = 7, size3 = 3;
    auto arr1 = new int[]{2, 5, 13, 7, 4};
    auto arr2 = new char[]{'a', 'b', 'c', '%', 'd', 'e', 'f'};
    auto arr3 = new double[]{1.3, 4.5, 10.99};

    //// Constructor:
    DynamicArray<int> Object1(arr1, size1);
    DynamicArray<char> Object2(arr2, size2);
    DynamicArray<double> Object3(arr3, size3);

    //// Copy constructor:
    DynamicArray<int> Object5(Object1);

    std::cout << "\nData before transformations:\n";
    Object1.Print(std::cout);
    Object2.Print(std::cout);
    Object3.Print(std::cout);
    Object5.Print(std::cout);

    //// Move constructor:
    DynamicArray<int> Object4 = std::move(Object5);
    Object4.Print(std::cout);

    //// Get:
    assert(Object1.GetSize() == 5);
    assert(Object2.GetSize() == 7);
    assert(Object3.GetSize() == 3);
    assert(Object4.GetSize() == Object1.GetSize());

    assert(Object1.Get(0) == 2);
    assert(Object2.Get(3) == '%');
    assert((Object3.Get(Object3.GetSize() - 1)) == 10.99);

    //// Set:
    Object1.Set(0, 1000);
    Object2.Set(Object2.GetSize() - 1, 'F');
    Object3.Set(Object3.GetSize(), 3000.55);
    Object4.Set(2, 4000);

    assert(Object1[0] == 1000);
    assert(Object2[Object2.GetSize() - 1] == 'F');
    assert(Object3[Object3.GetSize() - 1] == 3000.55);
    assert(Object4[2] == 4000);

    std::cout << "\nData after transformations:\n";
    Object1.Print(std::cout);
    Object2.Print(std::cout);
    Object3.Print(std::cout);
    Object4.Print(std::cout);

    //// Operators:
    assert(Object1[0] == 1000 && Object1[1] == 5 && Object1[2] == 13 && Object1[3] == 7 && Object1[4] == 4);
    assert(Object4 < Object1);
    assert(Object1 > Object4);
    assert(Object1 != Object4);
    {
        size_t size = Object3.GetSize();
        auto arr = new double[]{1.3, 4.5, 10.99, 3000.55};
        DynamicArray<double> Object(arr, size);

        assert(Object == Object3);
        assert(Object <= Object3);
        assert(Object >= Object3);

        delete[] arr;
    }

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
}

void TestLinkedList() {
    std::cout << "\n\tTest Linked List:\t\n";

    size_t size1 = 6, size2 = 4, size3 = 3;
    auto arr1 = new int[]{0, 11, 22, 33, 44, 55};
    auto arr2 = new std::string[]{"Renata", "Dora", "Tatty", "Maria"};
    auto arr3 = new double[]{1.3, 4.5, 5.21};

    //// Constructor:
    LinkedList<int> Object1(arr1, size1);
    LinkedList<std::string>* Object2 = new LinkedList<std::string>(arr2, size2);
    LinkedList<double>* Object3 = new LinkedList<double>(arr3, size3);

    //// Copy constructor:
    LinkedList<int> Object5(Object1);

    std::cout << "\nData before transformations:\n";
    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object5.Print(std::cout);

    //// Move constructor:
    LinkedList<int> Object4 = std::move(Object5);
    Object4.Print(std::cout);

    std::cout << std::endl;

    //// Get:
    assert(Object1.GetFirst() == 0);
    assert(Object2->GetFirst() == "Renata");
    assert(Object3->GetFirst() == 1.3);
    assert(Object4.GetFirst() == Object1.GetFirst());

    assert(Object1.GetLast() == 55);
    assert(Object2->GetLast() == "Maria");
    assert(Object3->GetLast() == 5.21);
    assert(Object4.GetLast() == Object1.GetLast());

    assert(Object1.Get(1) == 11);
    assert(Object2->Get(2) == "Tatty");
    assert(Object3->Get(1) == 4.5);
    assert(Object4.Get(4) == Object1.Get(4));

    assert(Object1.GetLength() == 6);
    assert(Object2->GetLength() == 4);
    assert(Object3->GetLength() == 3);
    assert(Object4.GetLength() == Object1.GetLength());

    {
        std::cout << "Test GetSubList function:\n";
        LinkedList<int> list1test(new int[]{11, 22, 33, 44}, 4);
        LinkedList<std::string>* list2test = new LinkedList<std::string>(new std::string[]{"Dora", "Tatty"}, 2);
        LinkedList<double>* list3test = new LinkedList<double>(new double[]{1.3, 4.5, 5.21}, 3);
        LinkedList<int> list4test(new int[]{55}, 1);

        LinkedList<int>* list1 = Object1.GetSubList(1, (int) Object1.GetLength() - 2);
        list1->Print(std::cout);

        LinkedList<std::string>* list2 = Object2->GetSubList(1, 2);
        list2->Print(std::cout);

        LinkedList<double>* list3 = Object3->GetSubList(0, 2);
        list3->Print(std::cout);

        LinkedList<int>* list4 = Object4.GetSubList(5, 5);
        list4->Print(std::cout);

        assert(*Object1.GetSubList(1, Object1.GetLength() - 2) == list1test);
        assert(*Object2->GetSubList(1, 2) == *list2test);
        assert(*Object3->GetSubList(0, Object3->GetLength() - 1) == *list3test);
        assert(*Object4.GetSubList(5, 5) == list4test);

        delete list2test;
        delete list3test;
    }

    //// Append, Prepend, InsertAt:
    Object1.Append(100);
    Object2->Append("Tagir");
    Object3->Append(7.34);
    Object4.Append(123);

    Object1.Prepend(300);
    Object2->Prepend("Tatiana Innokentievna");
    Object3->Prepend(100.125);
    Object4.Prepend(700);

    Object1.InsertAt(-150, 3);
    Object2->InsertAt("kitten", 2);
    Object3->InsertAt(900.1, 4);
    Object4.InsertAt(800, 1);

    assert(Object1.GetFirst() ==  300 && Object1.Get(3) == -150 && Object1.GetLast() == 100 && Object1.GetLength() == 9);
    assert(Object2->GetFirst() == "Tatiana Innokentievna" && Object2->Get(2) == "kitten" && Object2->GetLast() == "Tagir" && Object2->GetLength() == 7);
    assert(Object3->GetFirst() == 100.125 && Object3->Get(4) == 900.1 && Object3->GetLast() == 7.34 && Object3->GetLength() == 6);
    assert(Object4.GetFirst() == 700 && Object4.Get(1) == 800 && Object4.GetLast() == 123 && Object4.GetLength() == 9);

    Object1.Insert(299, Object1.begin());
    Object2->Insert("Varya", Object2->end());
    Object3->Insert(29.9, ++(++Object3->begin()));
    Object4.Insert(24, --Object4.end());

    assert(Object1.GetFirst() == 299);
    assert(Object2->GetLast() == "Varya");
    assert(Object3->Get(2) == 29.9);
    assert(Object4.Get(8) == 24);

    std::cout << "\nData after Append, Prepend, InsertAt and Insert functions:\n";
    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object4.Print(std::cout);

    {
        LinkedList<int>* test1 = new LinkedList<int>(new int[]{1, 2, 3}, 3);
        LinkedList<int>* test2 = new LinkedList<int>(new int[]{4,  5}, 2);

        LinkedList<int>* res1 = new LinkedList<int>(new int[]{1, 2, 3, 4,  5}, 5);

        LinkedList<char>* test3 = new LinkedList<char>(new char[]{'a', 'b', 'c'}, 3);
        LinkedList<char>* test4 = new LinkedList<char>(new char[]{'x', 'y', 'z', 'w'}, 4);

        LinkedList<char>* res2 = new LinkedList<char>(new char[]{'a', 'b', 'c', 'x', 'y', 'z', 'w'}, 7);

        std::cout << "\nTest Concat function:\n";

        assert(*test1->Concat(test2) == *res1);
        assert(*test3->Concat(test4) == *res2);

        test1->Print(std::cout);
        test3->Print(std::cout);

        delete test1;
        delete test2;
        delete test3;
        delete test4;

        delete res1;
        delete res2;
    }

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;

    delete Object2;
    delete Object3;

    std::cout<< std::endl;
}

void TestArraySequence() {
    std::cout << "\n\tTest Array Sequence:\t\n";

    //// Constructor:
    ArraySequence<int> Object1(new int[]{1, 2, 3, 4}, 4);
    ArraySequence<char>* Object2 = new ArraySequence(new char[]{'R', 'e', 'n', 'a', 't', 'a'}, 6);
    ArraySequence<double>* Object3 = new ArraySequence(new double[]{0, 1.1, 2.2}, 3);

    //// Copy constructor:
    ArraySequence<int> Object5(Object1);

    std::cout << "\nData before transformations:\n";
    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object5.Print(std::cout);

    //// Move constructor:
    ArraySequence<int> Object4 = std::move(Object5);
    Object4.Print(std::cout);

    //// Get:
    assert(Object1.GetFirst() == 1);
    assert(Object2->GetFirst() == 'R');
    assert(Object3->GetFirst() == 0);
    assert(Object4.GetFirst() == 1);

    assert(Object1.GetLast() == 4);
    assert(Object2->GetLast() == 'a');
    assert(Object3->GetLast() == 2.2);
    assert(Object4.GetLast() == 4);

    assert(Object1.Get(1) == 2);
    assert(Object2->Get(3) == 'a');
    assert((Object3->Get(Object3->GetLength() - 2)) == 1.1);


    {
        //// GetSubsequence:
        Sequence<int>* test1 = new ArraySequence<int>(new int[]{2, 3}, 2);
        Sequence<char>* test2 = new ArraySequence<char>(new char[]{'a', 't', 'a'}, 3);
        Sequence<double>* test3 = new ArraySequence<double>(new double[]{0, 1.1, 2.2}, 3);

        assert(*dynamic_cast<ArraySequence<int>*>(Object1.GetSubsequence(1, 2))
                == *dynamic_cast<ArraySequence<int>*>(test1));

        assert(*dynamic_cast<ArraySequence<char>*>(Object2->GetSubsequence(3, 5))
                == *dynamic_cast<ArraySequence<char>*>(test2));

        assert(*dynamic_cast<ArraySequence<double>*>(Object3->GetSubsequence(0, 2))
                == *dynamic_cast<ArraySequence<double>*>(test3));

        assert(*dynamic_cast<ArraySequence<int>*>(Object4.GetSubsequence(0, 2))
                == *dynamic_cast<ArraySequence<int>*>(Object1.GetSubsequence(0, 2)));

        std::cout << "\nTest GetSubsequence function:\n";
        Object1.GetSubsequence(1, 2)->Print(std::cout);
        Object2->GetSubsequence(3, 5)->Print(std::cout);
        Object3->GetSubsequence(0, 2)->Print(std::cout);
        Object4.GetSubsequence(0, 2)->Print(std::cout);

        delete test1;
        delete test2;
        delete test3;
    }


    assert(Object1.GetLength() == 4);
    assert(Object2->GetLength() == 6);
    assert(Object3->GetLength() == 3);
    assert(Object4.GetLength() == Object1.GetLength());

    //// Append, Prepend, InsertAt:
    Object1.Append(1000);
    Object2->Append('F');
    Object3->Append(3000.55);
    Object4.Append(4000);

    assert(Object1.GetLast() == 1000);
    assert(Object2->GetLast() == 'F');
    assert(Object3->GetLast() == 3000.55);
    assert(Object4.GetLast() == 4000);

    Object1.Prepend(0);
    Object2->Prepend('B');
    Object3->Prepend(-1.1);
    Object4.Prepend(0);

    assert(Object1.GetFirst() == 0);
    assert(Object2->GetFirst() == 'B');
    assert(Object3->GetFirst() == -1.1);
    assert(Object4.GetFirst() == 0);

    Object1.InsertAt(1, 1);
    Object2->InsertAt('P', 0);
    Object3->InsertAt(3.3, Object3->GetLength() - 1);
    Object4.InsertAt(300, 1);

    assert(Object1.Get(1) == 1);
    assert(Object2->Get(0) == 'P');
    assert(Object3->Get(Object3->GetLength() - 1) == 3.3);
    assert(Object4.Get(1) == 300);

    std::cout << "\nData after transformations:\n";
    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object4.Print(std::cout);

    {
        //// Concat:
        Sequence<int>* test1 = new ArraySequence<int>(new int[]{15, 25}, 2);
        Sequence<int>* test2 = new ArraySequence<int>(new int[]{35, 45}, 2);

        Sequence<int>* res1 = new ArraySequence<int>(new int[]{15, 25, 35, 45}, 4);

        Sequence<char>* test3 = new ArraySequence<char>(new char[]{'T', 'a', 'g'}, 3);
        Sequence<char>* test4 = new ArraySequence<char>(new char[]{'i', 'r'}, 2);

        Sequence<char>* res2 = new ArraySequence<char>(new char[]{'T', 'a', 'g', 'i', 'r'}, 5);

//        assert(*dynamic_cast<ArraySequence<int>*>(test1->Concat(test2))
//               == *dynamic_cast<ArraySequence<int>*>(res1));

//        assert(*dynamic_cast<ArraySequence<char>*>(test3->Concat(test4))
//               == *dynamic_cast<ArraySequence<char>*>(res2));
//
        std::cout << "\nTest Concat function:\n";
        test1->Concat(test2)->Print(std::cout);
        test3->Concat(test4)->Print(std::cout);

        delete test1;
        delete test2;
        delete test3;
        delete test4;

        delete res1;
        delete res2;
    }

    delete Object2;
    delete Object3;
}

void TestLinkedListSequence() {
    std::cout << "\n\tTest Linked List Sequence:\t\n";

    //// Constructor:
    LinkedListSequence<int> Object1(new int[]{1, 2, 3, 4}, 4);
    LinkedListSequence<char>* Object2 = new LinkedListSequence(new char[]{'R', 'e', 'n', 'a', 't', 'a'}, 6);
    LinkedListSequence<double>* Object3 = new LinkedListSequence(new double[]{0, 1.1, 2.2}, 3);

    //// Copy constructor:
    LinkedListSequence<int> Object5(Object1);

    std::cout << "\nData before transformations:\n";
    Object1.Print(std::cout);
    Object2->Print(std::cout);
    Object3->Print(std::cout);
    Object5.Print(std::cout);

    //// Move constructor:
    LinkedListSequence<int> Object4 = std::move(Object5);
    Object4.Print(std::cout);

    //// Get:
    assert(Object1.GetFirst() == 1);
    assert(Object2->GetFirst() == 'R');
    assert(Object3->GetFirst() == 0);
    assert(Object4.GetFirst() == 1);

    assert(Object1.GetLast() == 4);
    assert(Object2->GetLast() == 'a');
    assert(Object3->GetLast() == 2.2);
    assert(Object4.GetLast() == 4);

    assert(Object1.Get(1) == 2);
    assert(Object2->Get(3) == 'a');
    assert((Object3->Get(Object3->GetLength() - 2)) == 1.1);


//    {
//        //// GetSubsequence:
//        Sequence<int>* test1 = new LinkedListSequence<int>(new int[]{2, 3}, 2);
//        Sequence<char>* test2 = new LinkedListSequence<char>(new char[]{'a', 't', 'a'}, 3);
//        Sequence<double>* test3 = new LinkedListSequence<double>(new double[]{0, 1.1, 2.2}, 3);
//
//        assert(*dynamic_cast<ArraySequence<int>*>(Object1.GetSubsequence(1, 2))
//               == *dynamic_cast<ArraySequence<int>*>(test1));
//
//        assert(*dynamic_cast<ArraySequence<char>*>(Object2->GetSubsequence(3, 5))
//               == *dynamic_cast<ArraySequence<char>*>(test2));
//
//        assert(*dynamic_cast<ArraySequence<double>*>(Object3->GetSubsequence(0, 2))
//               == *dynamic_cast<ArraySequence<double>*>(test3));
//
//        assert(*dynamic_cast<ArraySequence<int>*>(Object4.GetSubsequence(0, 2))
//               == *dynamic_cast<ArraySequence<int>*>(Object1.GetSubsequence(0, 2)));
//
//        std::cout << "\nTest GetSubsequence function:\n";
//        Object1.GetSubsequence(1, 2)->Print(std::cout);
//        Object2->GetSubsequence(3, 5)->Print(std::cout);
//        Object3->GetSubsequence(0, 2)->Print(std::cout);
//        Object4.GetSubsequence(0, 2)->Print(std::cout);
//
//        delete test1;
//        delete test2;
//        delete test3;
//    }
//
//
//    assert(Object1.GetLength() == 4);
//    assert(Object2->GetLength() == 6);
//    assert(Object3->GetLength() == 3);
//    assert(Object4.GetLength() == Object1.GetLength());
//
//    //// Append, Prepend, InsertAt:
//    Object1.Append(1000);
//    Object2->Append('F');
//    Object3->Append(3000.55);
//    Object4.Append(4000);
//
//    assert(Object1.GetLast() == 1000);
//    assert(Object2->GetLast() == 'F');
//    assert(Object3->GetLast() == 3000.55);
//    assert(Object4.GetLast() == 4000);
//
//    Object1.Prepend(0);
//    Object2->Prepend('B');
//    Object3->Prepend(-1.1);
//    Object4.Prepend(0);
//
//    assert(Object1.GetFirst() == 0);
//    assert(Object2->GetFirst() == 'B');
//    assert(Object3->GetFirst() == -1.1);
//    assert(Object4.GetFirst() == 0);
//
//    Object1.InsertAt(1, 1);
//    Object2->InsertAt('P', 0);
//    Object3->InsertAt(3.3, Object3->GetLength() - 1);
//    Object4.InsertAt(300, 1);
//
//    assert(Object1.Get(1) == 1);
//    assert(Object2->Get(0) == 'P');
//    assert(Object3->Get(Object3->GetLength() - 1) == 3.3);
//    assert(Object4.Get(1) == 300);
//
//    std::cout << "\nData after transformations:\n";
//    Object1.Print(std::cout);
//    Object2->Print(std::cout);
//    Object3->Print(std::cout);
//    Object4.Print(std::cout);
//
//    {
//        //// Concat:
//        Sequence<int>* test1 = new ArraySequence<int>(new int[]{15, 25}, 2);
//        Sequence<int>* test2 = new ArraySequence<int>(new int[]{35, 45}, 2);
//
//        Sequence<int>* res1 = new ArraySequence<int>(new int[]{15, 25, 35, 45}, 4);
//
//        Sequence<char>* test3 = new ArraySequence<char>(new char[]{'T', 'a', 'g'}, 3);
//        Sequence<char>* test4 = new ArraySequence<char>(new char[]{'i', 'r'}, 2);
//
//        Sequence<char>* res2 = new ArraySequence<char>(new char[]{'T', 'a', 'g', 'i', 'r'}, 5);
//
////        assert(*dynamic_cast<ArraySequence<int>*>(test1->Concat(test2))
////               == *dynamic_cast<ArraySequence<int>*>(res1));
//
////        assert(*dynamic_cast<ArraySequence<char>*>(test3->Concat(test4))
////               == *dynamic_cast<ArraySequence<char>*>(res2));
////
//        std::cout << "\nTest Concat function:\n";
//        test1->Concat(test2)->Print(std::cout);
//        test3->Concat(test4)->Print(std::cout);
//
//        delete test1;
//        delete test2;
//        delete test3;
//        delete test4;
//
//        delete res1;
//        delete res2;
//    }

    delete Object2;
    delete Object3;
}

int main() {
    TestDynamicArray();
    TestLinkedList();
    TestArraySequence();
    TestLinkedListSequence();

    return 0;
}
