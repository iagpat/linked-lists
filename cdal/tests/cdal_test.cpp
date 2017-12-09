//Simple Singly-Linked List (SSLL)
// - A basic implementation: whenever an item is added to the list, a new node is allocated to hold it; whenever an item is removed, the node that held it is deallocated.
//
// by Iago Patiño López
// with content from https://www.cise.ufl.edu/~dts/ as well as "Algorithms in C++ by Robert Segewick"
#include <iostream>
#include <valarray>
#include <string>
#include <sstream>
#define DEBUG

//List ADTs included below:
#include "CDAL.h"



//Catch testing file included below:
#define CATCH_CONFIG_MAIN
#include "catch.h"

using namespace cop3530;

//The contains method needs an equals function to be passed in. This function cannot be declared inside the TEST CASE.

bool equals_function(const int& a, const int& b) {
    return a == b;
}

class person {
public:
    int age;

    person() : person(0) {
    }

    person(int age) : age(age) {
    }

    inline bool operator==(const person& c) const {
        return age == c.age;
    }

    inline friend std::ostream& operator<<(std::ostream& stream, const person& c) {
        return stream << c.age;
    }

    void set_age(int years) {
        age = years;
    }

    int get_age() {
        return age;
    }
};

TEST_CASE("Testing each method of the CDAL", "[CDAL]") {

    //Basic Functions

    SECTION("Testing push_back() and pop_back()") {

        CDAL<int> *test_cdal_1 = new CDAL<int>;

        test_cdal_1->push_back(1);

        test_cdal_1->push_back(2);

        test_cdal_1->push_back(3);

        test_cdal_1->push_back(4);

        REQUIRE(test_cdal_1->pop_back() == 4);

        REQUIRE(test_cdal_1->pop_back() == 3);

        REQUIRE(test_cdal_1->pop_back() == 2);

        REQUIRE(test_cdal_1->pop_back() == 1);
    }

    SECTION("Testing push_front() and pop_front()") {
        CDAL<int> *test_cdal_2 = new CDAL<int>;
        test_cdal_2->push_front(1);
        test_cdal_2->push_front(2);
        test_cdal_2->push_front(3);
        test_cdal_2->push_front(4);

        REQUIRE(test_cdal_2->pop_front() == 4);
        REQUIRE(test_cdal_2->pop_front() == 3);
        REQUIRE(test_cdal_2->pop_front() == 2);
        REQUIRE(test_cdal_2->pop_front() == 1);
    }

    SECTION("Testing insert()") {
        CDAL<int> *test_cdal_3 = new CDAL<int>;

        REQUIRE_THROWS(test_cdal_3->insert(0, -1));

        test_cdal_3->insert(5, 0);
        test_cdal_3->insert(3, 0);
        test_cdal_3->insert(2, 0);
        test_cdal_3->insert(1, 0);
        test_cdal_3->insert(0, 0);
        test_cdal_3->insert(4, 4);
        test_cdal_3->insert(0, 6);

        REQUIRE(test_cdal_3->item_at(0) == 0);
        REQUIRE(test_cdal_3->item_at(1) == 1);
        REQUIRE(test_cdal_3->item_at(2) == 2);
        REQUIRE(test_cdal_3->item_at(3) == 3);
        REQUIRE(test_cdal_3->item_at(4) == 4);
        REQUIRE(test_cdal_3->item_at(5) == 5);
    }

    SECTION("Testing remove()") {
        CDAL<int> *test_cdal_4 = new CDAL<int>;

        test_cdal_4->push_back(0);
        test_cdal_4->push_back(1);
        test_cdal_4->push_back(2);
        test_cdal_4->push_back(3);

        REQUIRE_THROWS(test_cdal_4->remove(4));
        REQUIRE(test_cdal_4->remove(3) == 3);
        REQUIRE(test_cdal_4->remove(2) == 2);
        REQUIRE(test_cdal_4->remove(1) == 1);
        REQUIRE(test_cdal_4->remove(0) == 0);
        REQUIRE_THROWS(test_cdal_4->remove(-1));
    }

    SECTION("Testing is_empty()") {
        CDAL<int> *test_cdal_5 = new CDAL<int>;
        REQUIRE(test_cdal_5->is_empty() == true);
        test_cdal_5->push_front(1);
        REQUIRE(test_cdal_5->is_empty() == false);
    }

    SECTION("Testing is_full()") {
        CDAL<int> *test_cdal_6 = new CDAL<int>;
        REQUIRE(test_cdal_6->is_full() == false);
    }

    SECTION("Testing length()") {
        CDAL<int> *test_cdal_7 = new CDAL<int>;

        test_cdal_7->push_back(1);
        test_cdal_7->push_back(2);
        test_cdal_7->push_back(3);
        test_cdal_7->push_back(4);

        REQUIRE(test_cdal_7->length() == 4);
    }

    SECTION("Testing peek_back()") {
        CDAL<int> *test_cdal_8 = new CDAL<int>;

        REQUIRE_THROWS(test_cdal_8->peek_back());

        test_cdal_8->push_back(1);
        test_cdal_8->push_back(2);
        test_cdal_8->push_back(3);
        test_cdal_8->push_back(4);

        REQUIRE(test_cdal_8->peek_back() == 4);
    }

    SECTION("Testing peek_front()") {
        CDAL<int> *test_cdal_9 = new CDAL<int>;

        REQUIRE_THROWS(test_cdal_9->peek_front());

        test_cdal_9->push_back(1);
        test_cdal_9->push_back(2);
        test_cdal_9->push_back(3);
        test_cdal_9->push_back(4);

        REQUIRE(test_cdal_9->peek_front() == 1);


    }

    SECTION("Testing item_at()") {
        CDAL<int> *test_cdal_10 = new CDAL<int>;

        test_cdal_10->push_back(1);
        test_cdal_10->push_back(2);
        test_cdal_10->push_back(3);
        test_cdal_10->push_back(4);

        REQUIRE_THROWS(test_cdal_10->item_at(-1));
        REQUIRE_THROWS(test_cdal_10->item_at(4));
        REQUIRE(test_cdal_10->item_at(0) == 1);
        REQUIRE(test_cdal_10->item_at(1) == 2);
        REQUIRE(test_cdal_10->item_at(2) == 3);
        REQUIRE(test_cdal_10->item_at(3) == 4);


    }

    SECTION("Testing clear()") {
        CDAL<int> *test_cdal_11 = new CDAL<int>;

        test_cdal_11->push_back(1);
        test_cdal_11->push_back(2);
        test_cdal_11->push_back(3);
        test_cdal_11->push_back(4);
        test_cdal_11->clear();

        REQUIRE(test_cdal_11->is_empty() == 1);


    }

    SECTION("Testing replace()") {
        CDAL<int> *test_cdal_12 = new CDAL<int>;

        test_cdal_12->push_back(0);
        test_cdal_12->push_back(1);
        test_cdal_12->push_back(2);
        test_cdal_12->push_back(3);
        test_cdal_12->push_back(4);

        REQUIRE_THROWS(test_cdal_12->replace(5, -1));

        REQUIRE(test_cdal_12->replace(4, 0) == 0);
        REQUIRE(test_cdal_12->replace(3, 1) == 1);
        REQUIRE(test_cdal_12->replace(2, 2) == 2);
        REQUIRE(test_cdal_12->replace(1, 3) == 3);
        REQUIRE(test_cdal_12->replace(0, 4) == 4);

        REQUIRE_THROWS(test_cdal_12->replace(-1, 5));

        REQUIRE(test_cdal_12->pop_back() == 0);
        REQUIRE(test_cdal_12->pop_back() == 1);
        REQUIRE(test_cdal_12->pop_back() == 2);
        REQUIRE(test_cdal_12->pop_back() == 3);
        REQUIRE(test_cdal_12->pop_back() == 4);



    }

    SECTION("Testing contents()") {
        CDAL<int> *test_cdal_13 = new CDAL<int>;

        test_cdal_13->push_back(0);
        test_cdal_13->push_back(1);
        test_cdal_13->push_back(2);
        test_cdal_13->push_back(3);
        int *array = test_cdal_13->contents();
        for (int i = 0; i < 4; i++)
            REQUIRE(array[i] == i);


    }

    SECTION("Testing print()") {
        CDAL<int> *test_cdal_14 = new CDAL<int>;

        std::ostringstream stream;
        test_cdal_14->print(stream);
        REQUIRE(stream.str() == "<empty list>\n");
        test_cdal_14->push_back(0);
        test_cdal_14->push_back(1);
        test_cdal_14->push_back(2);
        test_cdal_14->push_back(3);
        test_cdal_14->print(stream);
        REQUIRE(stream.str() == "<empty list>\n[0,1,2,3]");


    }

    SECTION("Testing contains()") {
        CDAL<int> *test_cdal_15 = new CDAL<int>;

        test_cdal_15->push_back(1);
        test_cdal_15->push_back(2);
        test_cdal_15->push_back(3);
        test_cdal_15->push_back(4);
        REQUIRE(test_cdal_15->contains(0, equals_function) == false);
        REQUIRE(test_cdal_15->contains(1, equals_function) == true);
        REQUIRE(test_cdal_15->contains(2, equals_function) == true);
        REQUIRE(test_cdal_15->contains(3, equals_function) == true);
        REQUIRE(test_cdal_15->contains(4, equals_function) == true);


    }

    //ITERATOR TESTING

    SECTION("Testing begin()") {
        CDAL<int> *test_cdal_16 = new CDAL<int>;

        REQUIRE_THROWS(test_cdal_16->begin());

        test_cdal_16->push_front(1);

        cop3530::CDAL<int>::iterator test_cdal_16_iterator = test_cdal_16->begin();

        REQUIRE(test_cdal_16->peek_front() == *test_cdal_16_iterator);

    }

    SECTION("Testing end()") {
        CDAL<int> *test_cdal_17 = new CDAL<int>;

        REQUIRE_THROWS(test_cdal_17->end());
        test_cdal_17->push_back(1);
        cop3530::CDAL<int>::iterator test_cdal_17_iterator_end = test_cdal_17->end();
        cop3530::CDAL<int>::iterator test_cdal_17_iterator_begin = test_cdal_17->begin();
        REQUIRE(++test_cdal_17_iterator_begin == test_cdal_17_iterator_end);

    }

    SECTION("Testing operator++()") {
        CDAL<int> *test_cdal_18 = new CDAL<int>;

        test_cdal_18->push_back(0);
        test_cdal_18->push_back(1);
        test_cdal_18->push_back(2);
        test_cdal_18->push_back(3);
        test_cdal_18->push_back(4);

        cop3530::CDAL<int>::iterator test_cdal_18_iterator = test_cdal_18->begin();

        REQUIRE(*++test_cdal_18_iterator == 1);
        REQUIRE(*++test_cdal_18_iterator == 2);
        REQUIRE(*++test_cdal_18_iterator == 3);
        REQUIRE(*++test_cdal_18_iterator == 4);

    }

    SECTION("Testing operator++(int)") {
        CDAL<int> *test_cdal_19 = new CDAL<int>;

        test_cdal_19->push_back(0);
        test_cdal_19->push_back(1);
        test_cdal_19->push_back(2);
        test_cdal_19->push_back(3);
        test_cdal_19->push_back(4);

        cop3530::CDAL<int>::iterator test_cdal_19_iterator = test_cdal_19->begin();

        REQUIRE(*test_cdal_19_iterator++ == 0);
        REQUIRE(*test_cdal_19_iterator++ == 1);
        REQUIRE(*test_cdal_19_iterator++ == 2);
        REQUIRE(*test_cdal_19_iterator++ == 3);
        REQUIRE(*test_cdal_19_iterator++ == 4);

    }

    SECTION("Testing operator*()") {
        CDAL<int> *test_cdal_20 = new CDAL<int>;

        test_cdal_20->push_back(1);
        cop3530::CDAL<int>::iterator test_cdal_20_iterator = test_cdal_20->begin();
        *test_cdal_20_iterator = 2;
        REQUIRE(test_cdal_20->pop_back() == 2);

    }

    SECTION("Testing operator->()") {
        CDAL<int> *test_cdal_21 = new CDAL<int>;

        person james;
        person jorge;
        person thomas;

        CDAL<person> *test_cdal_person = new CDAL<person>;

        test_cdal_person->push_back(james);
        test_cdal_person->push_back(jorge);
        test_cdal_person->push_back(thomas);

        cop3530::CDAL<person>::iterator person_iterator = test_cdal_person->begin();

        person_iterator->set_age(45);

        REQUIRE(person_iterator->get_age() == 45);


    }

    SECTION("Testing operator==()") {
        CDAL<int> *test_cdal_22 = new CDAL<int>;

        test_cdal_22->push_back(0);
        test_cdal_22->push_back(1);

        cop3530::CDAL<int>::iterator iterator_begin = test_cdal_22->begin();
        cop3530::CDAL<int>::iterator iterator_end = test_cdal_22->end();

        iterator_begin++;
        iterator_begin++;

        REQUIRE(iterator_begin == iterator_end);
    }

    SECTION("Testing operator=()") {
        CDAL<int> *test_cdal_23 = new CDAL<int>;

        test_cdal_23->push_back(0);
        test_cdal_23->push_back(1);

        cop3530::CDAL<int>::iterator iterator_begin = test_cdal_23->begin();
        cop3530::CDAL<int>::iterator iterator_end = test_cdal_23->end();

        iterator_end = ++iterator_begin;

        REQUIRE(*iterator_end == 1);

    }

    SECTION("Testing operator!=()") {
        CDAL<int> *test_cdal_24 = new CDAL<int>;

        test_cdal_24->push_back(0);
        test_cdal_24->push_back(1);

        cop3530::CDAL<int>::iterator iterator_begin = test_cdal_24->begin();
        cop3530::CDAL<int>::iterator iterator_end = test_cdal_24->end();

        REQUIRE(iterator_begin != iterator_end);

    }

    SECTION("Complex multi-function test") {
        CDAL<int> *test_cdal_25 = new CDAL<int>;
        REQUIRE(test_cdal_25->is_empty());
        for (int i = 40; i >= 0; i--) {
            if (!(i % 2)) test_cdal_25->push_front(i); //If number is even, push
            else test_cdal_25->push_front(i);
        }
        REQUIRE(test_cdal_25->length() == 41);
        REQUIRE(!test_cdal_25->is_empty());
        REQUIRE(!test_cdal_25->is_full());
        REQUIRE(test_cdal_25->replace(99, 15) == 15);
        REQUIRE(test_cdal_25->item_at(15) == 99);
        REQUIRE(test_cdal_25->remove(14) == 14);
        test_cdal_25->insert(14, 14);
        REQUIRE(test_cdal_25->peek_front() == 0);
        REQUIRE(test_cdal_25->pop_front() == 0);
        REQUIRE(test_cdal_25->peek_back() == 40);
        REQUIRE(test_cdal_25->pop_back() == 40);
        REQUIRE(test_cdal_25->item_at(14) == 99);
        REQUIRE(test_cdal_25->contains(99, equals_function) == 1);
        std::ostringstream dtream;
        test_cdal_25->print(dtream);
        REQUIRE(dtream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39]");

    }

    SECTION("Testing copy constructor") {
        CDAL<int> *test_cdal_26 = new CDAL<int>;
        for (int i = 40; i >= 0; i--) {
            if (!(i % 2)) test_cdal_26->push_front(i);
            else test_cdal_26->push_front(i);
        }

        CDAL<int> *test_cdal_27 = new CDAL<int>(*test_cdal_26); //This calls the copy constructor

        //By doing the following operations with both lists we prove that we did a deep copy of the original list

        //Original list

        REQUIRE(test_cdal_26->length() == 41);
        REQUIRE(!test_cdal_26->is_empty());
        REQUIRE(!test_cdal_26->is_full());
        REQUIRE(test_cdal_26->replace(99, 15) == 15);
        REQUIRE(test_cdal_26->item_at(15) == 99);
        REQUIRE(test_cdal_26->remove(14) == 14);
        test_cdal_26->insert(14, 14);
        REQUIRE(test_cdal_26->peek_front() == 0);
        REQUIRE(test_cdal_26->pop_front() == 0);
        REQUIRE(test_cdal_26->peek_back() == 40);
        REQUIRE(test_cdal_26->pop_back() == 40);
        REQUIRE(test_cdal_26->item_at(14) == 99);
        REQUIRE(test_cdal_26->contains(99, equals_function) == 1);
        std::ostringstream dtream;
        test_cdal_26->print(dtream);
        REQUIRE(dtream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39]");

        //Copied list

        REQUIRE(test_cdal_27->length() == 41);
        REQUIRE(!test_cdal_27->is_empty());
        REQUIRE(!test_cdal_27->is_full());
        REQUIRE(test_cdal_27->replace(99, 15) == 15);
        REQUIRE(test_cdal_27->item_at(15) == 99);
        REQUIRE(test_cdal_27->remove(14) == 14);
        test_cdal_27->insert(14, 14);
        REQUIRE(test_cdal_27->peek_front() == 0);
        REQUIRE(test_cdal_27->pop_front() == 0);
        REQUIRE(test_cdal_27->peek_back() == 40);
        REQUIRE(test_cdal_27->pop_back() == 40);
        REQUIRE(test_cdal_27->item_at(14) == 99);
        REQUIRE(test_cdal_27->contains(99, equals_function) == 1);
        std::ostringstream btream;
        test_cdal_27->print(btream);
        REQUIRE(btream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39]");

    }

    SECTION("Testing move constructor") {
        CDAL<int> *test_cdal_28 = new CDAL<int>;
        for (int i = 40; i >= 0; i--) {
            if (!(i % 2)) test_cdal_28->push_front(i); //If number is even, push
            else test_cdal_28->push_front(i);
        }

        CDAL<int> *test_cdal_29 = new CDAL<int>(std::move(*test_cdal_28));

        REQUIRE(test_cdal_28->length() == 0); //This line guarantees that the original list was cleared

        //The following lines of code proof that the created list is equivalent to the original list before the move operation
        REQUIRE(test_cdal_29->length() == 41);
        REQUIRE(!test_cdal_29->is_empty());
        REQUIRE(!test_cdal_29->is_full());
        REQUIRE(test_cdal_29->replace(99, 15) == 15);
        REQUIRE(test_cdal_29->item_at(15) == 99);
        REQUIRE(test_cdal_29->remove(14) == 14);
        test_cdal_29->insert(14, 14);
        REQUIRE(test_cdal_29->peek_front() == 0);
        REQUIRE(test_cdal_29->pop_front() == 0);
        REQUIRE(test_cdal_29->peek_back() == 40);
        REQUIRE(test_cdal_29->pop_back() == 40);
        REQUIRE(test_cdal_29->item_at(14) == 99);
        REQUIRE(test_cdal_29->contains(99, equals_function) == 1);
        std::ostringstream dtream;
        test_cdal_29->print(dtream);
        REQUIRE(dtream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39]");

    }

    SECTION("Testing copy assignment operator") {
        CDAL<int> *test_cdal_30 = new CDAL<int>;

        for (int i = 40; i >= 0; i--) {
            if (!(i % 2)) test_cdal_30->push_front(i);
            else test_cdal_30->push_front(i);
        }

        CDAL<int> *test_cdal_31 = new CDAL<int>; //Declare a new list
        *test_cdal_31 = *test_cdal_30; //Copy the list using a copy assignment operator

        //By doing the following operations with both lists we prove that we did a deep copy of the original list

        //Original list
        REQUIRE(test_cdal_30->length() == 41);
        REQUIRE(!test_cdal_30->is_empty());
        REQUIRE(!test_cdal_30->is_full());
        REQUIRE(test_cdal_30->replace(99, 15) == 15);
        REQUIRE(test_cdal_30->item_at(15) == 99);
        REQUIRE(test_cdal_30->remove(14) == 14);
        test_cdal_30->insert(14, 14);
        REQUIRE(test_cdal_30->peek_front() == 0);
        REQUIRE(test_cdal_30->pop_front() == 0);
        REQUIRE(test_cdal_30->peek_back() == 40);
        REQUIRE(test_cdal_30->pop_back() == 40);
        REQUIRE(test_cdal_30->item_at(14) == 99);
        REQUIRE(test_cdal_30->contains(99, equals_function) == 1);
        std::ostringstream dtream;
        test_cdal_30->print(dtream);
        REQUIRE(dtream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39]");

        //Copied list
        REQUIRE(test_cdal_31->length() == 41);
        REQUIRE(!test_cdal_31->is_empty());
        REQUIRE(!test_cdal_31->is_full());
        REQUIRE(test_cdal_31->replace(99, 15) == 15);
        REQUIRE(test_cdal_31->item_at(15) == 99);
        REQUIRE(test_cdal_31->remove(14) == 14);
        test_cdal_31->insert(14, 14);
        REQUIRE(test_cdal_31->peek_front() == 0);
        REQUIRE(test_cdal_31->pop_front() == 0);
        REQUIRE(test_cdal_31->peek_back() == 40);
        REQUIRE(test_cdal_31->pop_back() == 40);
        REQUIRE(test_cdal_31->item_at(14) == 99);
        REQUIRE(test_cdal_31->contains(99, equals_function) == 1);
        std::ostringstream btream;
        test_cdal_31->print(btream);
        REQUIRE(btream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39]");

    }

    SECTION("Testing move assignment operator") {
        CDAL<int> *test_cdal_32 = new CDAL<int>;

        for (int i = 40; i >= 0; i--) {
            if (!(i % 2)) test_cdal_32->push_front(i);
            else test_cdal_32->push_front(i);
        }

        CDAL<int> *test_cdal_33 = new CDAL<int>; //Declare a new list
        *test_cdal_33 = std::move(*test_cdal_32); //Use the move assignment operator to "move" the original list into the new list

        REQUIRE(test_cdal_32->length() == 0); //This line guarantees that the original list was cleared

        //The following lines of code proof that the created list is equivalent to the original list before the move operation
        REQUIRE(test_cdal_33->length() == 41);
        REQUIRE(!test_cdal_33->is_empty());
        REQUIRE(!test_cdal_33->is_full());
        REQUIRE(test_cdal_33->replace(99, 15) == 15);
        REQUIRE(test_cdal_33->item_at(15) == 99);
        REQUIRE(test_cdal_33->remove(14) == 14);
        test_cdal_33->insert(14, 14);
        REQUIRE(test_cdal_33->peek_front() == 0);
        REQUIRE(test_cdal_33->pop_front() == 0);
        REQUIRE(test_cdal_33->peek_back() == 40);
        REQUIRE(test_cdal_33->pop_back() == 40);
        REQUIRE(test_cdal_33->item_at(14) == 99);
        REQUIRE(test_cdal_33->contains(99, equals_function) == 1);
        std::ostringstream dtream;
        test_cdal_33->print(dtream);
        REQUIRE(dtream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39]");
    }

}
