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
#include "PSLL.h"



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

TEST_CASE("Testing each method of the PSLL", "[PSLL]") {

    //Basic Functions

    SECTION("Testing push_back() and pop_back()") {
        PSLL<int> *test_psll_1 = new PSLL<int>;

        test_psll_1->push_back(1);
        test_psll_1->push_back(2);
        test_psll_1->push_back(3);
        test_psll_1->push_back(4);

        REQUIRE(test_psll_1->pop_back() == 4);
        REQUIRE(test_psll_1->pop_back() == 3);
        REQUIRE(test_psll_1->pop_back() == 2);
        REQUIRE(test_psll_1->pop_back() == 1);

        delete test_psll_1;

    }

    SECTION("Testing push_front() and pop_front()") {
        PSLL<int> *test_psll_2 = new PSLL<int>;
        test_psll_2->push_front(1);
        test_psll_2->push_front(2);
        test_psll_2->push_front(3);
        test_psll_2->push_front(4);
        REQUIRE(test_psll_2->pop_front() == 4);
        REQUIRE(test_psll_2->pop_front() == 3);
        REQUIRE(test_psll_2->pop_front() == 2);
        REQUIRE(test_psll_2->pop_front() == 1);
        delete test_psll_2;
    }

    SECTION("Testing insert()") {
        PSLL<int> *test_psll_3 = new PSLL<int>;

        REQUIRE_THROWS(test_psll_3->insert(0, -1));

        test_psll_3->insert(5, 0);
        test_psll_3->insert(3, 0);
        test_psll_3->insert(2, 0);
        test_psll_3->insert(1, 0);
        test_psll_3->insert(0, 0);
        test_psll_3->insert(4, 4);
        test_psll_3->insert(0, 6);

        REQUIRE(test_psll_3->item_at(0) == 0);
        REQUIRE(test_psll_3->item_at(1) == 1);
        REQUIRE(test_psll_3->item_at(2) == 2);
        REQUIRE(test_psll_3->item_at(3) == 3);
        REQUIRE(test_psll_3->item_at(4) == 4);
        REQUIRE(test_psll_3->item_at(5) == 5);

        delete test_psll_3;

    }

    SECTION("Testing remove()") {
        PSLL<int> *test_psll_4 = new PSLL<int>;

        test_psll_4->push_back(0);
        test_psll_4->push_back(1);
        test_psll_4->push_back(2);
        test_psll_4->push_back(3);

        REQUIRE_THROWS(test_psll_4->remove(4));
        REQUIRE(test_psll_4->remove(3) == 3);
        REQUIRE(test_psll_4->remove(2) == 2);
        REQUIRE(test_psll_4->remove(1) == 1);
        REQUIRE(test_psll_4->remove(0) == 0);
        REQUIRE_THROWS(test_psll_4->remove(-1));

        delete test_psll_4;
    }

    SECTION("Testing is_empty()") {
        PSLL<int> *test_psll_5 = new PSLL<int>;

        REQUIRE(test_psll_5->is_empty() == true);
        test_psll_5->push_front(1);
        REQUIRE(test_psll_5->is_empty() == false);

        delete test_psll_5;

    }

    SECTION("Testing is_full()") {
        PSLL<int> *test_psll_6 = new PSLL<int>;

        REQUIRE(test_psll_6->is_full() == false);

        delete test_psll_6;
    }

    SECTION("Testing length()") {
        PSLL<int> *test_psll_7 = new PSLL<int>;

        test_psll_7->push_back(1);
        test_psll_7->push_back(2);
        test_psll_7->push_back(3);
        test_psll_7->push_back(4);

        REQUIRE(test_psll_7->length() == 4);

        delete test_psll_7;
    }

    SECTION("Testing peek_back()") {
        PSLL<int> *test_psll_8 = new PSLL<int>;

        REQUIRE_THROWS(test_psll_8->peek_back());

        test_psll_8->push_back(1);
        test_psll_8->push_back(2);
        test_psll_8->push_back(3);
        test_psll_8->push_back(4);

        REQUIRE(test_psll_8->peek_back() == 4);

        delete test_psll_8;

    }

    SECTION("Testing peek_front()") {
        PSLL<int> *test_psll_9 = new PSLL<int>;

        REQUIRE_THROWS(test_psll_9->peek_front());

        test_psll_9->push_back(1);
        test_psll_9->push_back(2);
        test_psll_9->push_back(3);
        test_psll_9->push_back(4);

        REQUIRE(test_psll_9->peek_front() == 1);

        delete test_psll_9;
    }

    SECTION("Testing item_at()") {
        PSLL<int> *test_psll_10 = new PSLL<int>;

        test_psll_10->push_back(1);
        test_psll_10->push_back(2);
        test_psll_10->push_back(3);
        test_psll_10->push_back(4);

        REQUIRE_THROWS(test_psll_10->item_at(-1));
        REQUIRE_THROWS(test_psll_10->item_at(4));
        REQUIRE(test_psll_10->item_at(0) == 1);
        REQUIRE(test_psll_10->item_at(1) == 2);
        REQUIRE(test_psll_10->item_at(2) == 3);
        REQUIRE(test_psll_10->item_at(3) == 4);

        delete test_psll_10;
    }

    SECTION("Testing clear()") {
        PSLL<int> *test_psll_11 = new PSLL<int>;

        test_psll_11->push_back(1);
        test_psll_11->push_back(2);
        test_psll_11->push_back(3);
        test_psll_11->push_back(4);
        test_psll_11->clear();

        REQUIRE(test_psll_11->is_empty() == 1);

        delete test_psll_11;
    }

    SECTION("Testing replace()") {
        PSLL<int> *test_psll_12 = new PSLL<int>;

        test_psll_12->push_back(0);
        test_psll_12->push_back(1);
        test_psll_12->push_back(2);
        test_psll_12->push_back(3);
        test_psll_12->push_back(4);

        REQUIRE_THROWS(test_psll_12->replace(5, -1));

        REQUIRE(test_psll_12->replace(4, 0) == 0);
        REQUIRE(test_psll_12->replace(3, 1) == 1);
        REQUIRE(test_psll_12->replace(2, 2) == 2);
        REQUIRE(test_psll_12->replace(1, 3) == 3);
        REQUIRE(test_psll_12->replace(0, 4) == 4);

        REQUIRE_THROWS(test_psll_12->replace(-1, 5));

        REQUIRE(test_psll_12->pop_back() == 0);
        REQUIRE(test_psll_12->pop_back() == 1);
        REQUIRE(test_psll_12->pop_back() == 2);
        REQUIRE(test_psll_12->pop_back() == 3);
        REQUIRE(test_psll_12->pop_back() == 4);

        delete test_psll_12;

    }

    SECTION("Testing contents()") {
        PSLL<int> *test_psll_13 = new PSLL<int>;

        test_psll_13->push_back(0);
        test_psll_13->push_back(1);
        test_psll_13->push_back(2);
        test_psll_13->push_back(3);
        int *array = test_psll_13->contents();
        for (int i = 0; i < 4; i++)
            REQUIRE(array[i] == i);

        delete test_psll_13;
    }

    SECTION("Testing print()") {
        PSLL<int> *test_psll_14 = new PSLL<int>;

        std::ostringstream stream;
        test_psll_14->print(stream);
        REQUIRE(stream.str() == "<empty list>\n");
        test_psll_14->push_back(0);
        test_psll_14->push_back(1);
        test_psll_14->push_back(2);
        test_psll_14->push_back(3);
        test_psll_14->print(stream);
        REQUIRE(stream.str() == "<empty list>\n[0,1,2,3]");

        delete test_psll_14;
    }

    SECTION("Testing contains()") {
        PSLL<int> *test_psll_15 = new PSLL<int>;

        test_psll_15->push_back(1);
        test_psll_15->push_back(2);
        test_psll_15->push_back(3);
        test_psll_15->push_back(4);
        REQUIRE(test_psll_15->contains(0, equals_function) == false);
        REQUIRE(test_psll_15->contains(1, equals_function) == true);
        REQUIRE(test_psll_15->contains(2, equals_function) == true);
        REQUIRE(test_psll_15->contains(3, equals_function) == true);
        REQUIRE(test_psll_15->contains(4, equals_function) == true);

        delete test_psll_15;
    }

    //ITERATOR TESTING

    SECTION("Testing begin()") {
        PSLL<int> *test_psll_16 = new PSLL<int>;

        REQUIRE_THROWS(test_psll_16->begin());

        test_psll_16->push_front(1);

        cop3530::PSLL<int>::iterator test_psll_16_iterator = test_psll_16->begin();

        REQUIRE(test_psll_16->peek_front() == *test_psll_16_iterator);

        delete test_psll_16;
    }

    SECTION("Testing end()") {
        PSLL<int> *test_psll_17 = new PSLL<int>;

        REQUIRE_THROWS(test_psll_17->end());
        test_psll_17->push_back(1);
        cop3530::PSLL<int>::iterator test_psll_17_iterator_end = test_psll_17->end();
        cop3530::PSLL<int>::iterator test_psll_17_iterator_begin = test_psll_17->begin();
        REQUIRE(++test_psll_17_iterator_begin == test_psll_17_iterator_end);

        delete test_psll_17;
    }

    SECTION("Testing operator++()") {
        PSLL<int> *test_psll_18 = new PSLL<int>;

        test_psll_18->push_back(0);
        test_psll_18->push_back(1);
        test_psll_18->push_back(2);
        test_psll_18->push_back(3);
        test_psll_18->push_back(4);

        cop3530::PSLL<int>::iterator test_psll_18_iterator = test_psll_18->begin();

        REQUIRE(*++test_psll_18_iterator == 1);
        REQUIRE(*++test_psll_18_iterator == 2);
        REQUIRE(*++test_psll_18_iterator == 3);
        REQUIRE(*++test_psll_18_iterator == 4);

        delete test_psll_18;

    }

    SECTION("Testing operator++(int)") {
        PSLL<int> *test_psll_19 = new PSLL<int>;

        test_psll_19->push_back(0);
        test_psll_19->push_back(1);
        test_psll_19->push_back(2);
        test_psll_19->push_back(3);
        test_psll_19->push_back(4);

        cop3530::PSLL<int>::iterator test_psll_19_iterator = test_psll_19->begin();

        REQUIRE(*test_psll_19_iterator++ == 0);
        REQUIRE(*test_psll_19_iterator++ == 1);
        REQUIRE(*test_psll_19_iterator++ == 2);
        REQUIRE(*test_psll_19_iterator++ == 3);
        REQUIRE(*test_psll_19_iterator++ == 4);

        delete test_psll_19;
    }

    SECTION("Testing operator*()") {
        PSLL<int> *test_psll_20 = new PSLL<int>;

        test_psll_20->push_back(1);
        cop3530::PSLL<int>::iterator test_psll_20_iterator = test_psll_20->begin();
        *test_psll_20_iterator = 2;
        REQUIRE(test_psll_20->pop_back() == 2);

        delete test_psll_20;
    }

    SECTION("Testing operator->()") {
        PSLL<int> *test_psll_21 = new PSLL<int>;

        person james;
        person jorge;
        person thomas;

        PSLL<person> *test_psll_person = new PSLL<person>;

        test_psll_person->push_back(james);
        test_psll_person->push_back(jorge);
        test_psll_person->push_back(thomas);

        cop3530::PSLL<person>::iterator person_iterator = test_psll_person->begin();

        person_iterator->set_age(45);

        REQUIRE(person_iterator->get_age() == 45);

        delete test_psll_21;

    }

    SECTION("Testing operator==()") {
        PSLL<int> *test_psll_22 = new PSLL<int>;

        test_psll_22->push_back(0);
        test_psll_22->push_back(1);

        cop3530::PSLL<int>::iterator iterator_begin = test_psll_22->begin();
        cop3530::PSLL<int>::iterator iterator_end = test_psll_22->end();

        iterator_begin++;
        iterator_begin++;
        REQUIRE(iterator_begin == iterator_end);

        delete test_psll_22;
    }

    SECTION("Testing operator=()") {
        PSLL<int> *test_psll_23 = new PSLL<int>;

        test_psll_23->push_back(0);
        test_psll_23->push_back(1);

        cop3530::PSLL<int>::iterator iterator_begin = test_psll_23->begin();
        cop3530::PSLL<int>::iterator iterator_end = test_psll_23->end();

        iterator_end = ++iterator_begin;

        REQUIRE(*iterator_end == 1);

        delete test_psll_23;
    }

    SECTION("Testing operator!=()") {
        PSLL<int> *test_psll_24 = new PSLL<int>;

        test_psll_24->push_back(0);
        test_psll_24->push_back(1);

        cop3530::PSLL<int>::iterator iterator_begin = test_psll_24->begin();
        cop3530::PSLL<int>::iterator iterator_end = test_psll_24->end();

        REQUIRE(iterator_begin != iterator_end);

        delete test_psll_24;
    }

    //OTHER

    SECTION("Complex multi-function test") {
        PSLL<int> *test_psll_25 = new PSLL<int>;
        REQUIRE(test_psll_25->is_empty());
        for (int i = 65; i >= 0; i--) {
            if (!(i % 2)) test_psll_25->push_front(i); //If number is even, push
            else test_psll_25->push_front(i);
        }
        REQUIRE(test_psll_25->length() == 66);
        REQUIRE(!test_psll_25->is_empty());
        REQUIRE(!test_psll_25->is_full());
        REQUIRE(test_psll_25->replace(99, 15) == 15);
        REQUIRE(test_psll_25->item_at(15) == 99);
        REQUIRE(test_psll_25->remove(14) == 14);
        test_psll_25->insert(14, 14);
        REQUIRE(test_psll_25->peek_front() == 0);
        REQUIRE(test_psll_25->pop_front() == 0);
        REQUIRE(test_psll_25->peek_back() == 65);
        REQUIRE(test_psll_25->pop_back() == 65);
        REQUIRE(test_psll_25->item_at(14) == 99);
        REQUIRE(test_psll_25->contains(99, equals_function) == 1);
        std::ostringstream dtream;
        test_psll_25->print(dtream);
        REQUIRE(dtream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64]");
        delete test_psll_25;
    }

    SECTION("Testing copy constructor") {
        PSLL<int> *test_psll_26 = new PSLL<int>;
        for (int i = 65; i >= 0; i--) {
            if (!(i % 2)) test_psll_26->push_front(i);
            else test_psll_26->push_front(i);
        }

        PSLL<int> *test_psll_27 = new PSLL<int>(*test_psll_26); //This calls the copy constructor

        //By doing the following operations with both lists we prove that we did a deep copy of the original list

        //Original list
        REQUIRE(test_psll_26->length() == 66);
        REQUIRE(!test_psll_26->is_empty());
        REQUIRE(!test_psll_26->is_full());
        REQUIRE(test_psll_26->replace(99, 15) == 15);
        REQUIRE(test_psll_26->item_at(15) == 99);
        REQUIRE(test_psll_26->remove(14) == 14);
        test_psll_26->insert(14, 14);
        REQUIRE(test_psll_26->peek_front() == 0);
        REQUIRE(test_psll_26->pop_front() == 0);
        REQUIRE(test_psll_26->peek_back() == 65);
        REQUIRE(test_psll_26->pop_back() == 65);
        REQUIRE(test_psll_26->item_at(14) == 99);
        REQUIRE(test_psll_26->contains(99, equals_function) == 1);
        std::ostringstream dtream;
        test_psll_26->print(dtream);
        REQUIRE(dtream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64]");

        //Copied list
        REQUIRE(test_psll_27->length() == 66);
        REQUIRE(!test_psll_27->is_empty());
        REQUIRE(!test_psll_27->is_full());
        REQUIRE(test_psll_27->replace(99, 15) == 15);
        REQUIRE(test_psll_27->item_at(15) == 99);
        REQUIRE(test_psll_27->remove(14) == 14);
        test_psll_27->insert(14, 14);
        REQUIRE(test_psll_27->peek_front() == 0);
        REQUIRE(test_psll_27->pop_front() == 0);
        REQUIRE(test_psll_27->peek_back() == 65);
        REQUIRE(test_psll_27->pop_back() == 65);
        REQUIRE(test_psll_27->item_at(14) == 99);
        REQUIRE(test_psll_27->contains(99, equals_function) == 1);
        std::ostringstream btream;
        test_psll_27->print(btream);
        REQUIRE(btream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64]");

        delete test_psll_27;
        delete test_psll_26;
    }

    SECTION("Testing move constructor") {
        PSLL<int> *test_psll_28 = new PSLL<int>;
        for (int i = 65; i >= 0; i--) {
            if (!(i % 2)) test_psll_28->push_front(i); //If number is even, push
            else test_psll_28->push_front(i);
        }

        PSLL<int> *test_psll_29 = new PSLL<int>(std::move(*test_psll_28));

        REQUIRE(test_psll_28->length() == 0); //This line guarantees that the original list was cleared

        //The following lines of code proof that the created list is equivalent to the original list before the move operation
        REQUIRE(test_psll_29->length() == 66);
        REQUIRE(!test_psll_29->is_empty());
        REQUIRE(!test_psll_29->is_full());
        REQUIRE(test_psll_29->replace(99, 15) == 15);
        REQUIRE(test_psll_29->item_at(15) == 99);
        REQUIRE(test_psll_29->remove(14) == 14);
        test_psll_29->insert(14, 14);
        REQUIRE(test_psll_29->peek_front() == 0);
        REQUIRE(test_psll_29->pop_front() == 0);
        REQUIRE(test_psll_29->peek_back() == 65);
        REQUIRE(test_psll_29->pop_back() == 65);
        REQUIRE(test_psll_29->item_at(14) == 99);
        REQUIRE(test_psll_29->contains(99, equals_function) == 1);
        std::ostringstream dtream;
        test_psll_29->print(dtream);
        REQUIRE(dtream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64]");


        delete test_psll_29;
        delete test_psll_28;

    }

    SECTION("Testing copy assignment operator") {
        PSLL<int> *test_psll_30 = new PSLL<int>;

        for (int i = 65; i >= 0; i--) {
            if (!(i % 2)) test_psll_30->push_front(i);
            else test_psll_30->push_front(i);
        }

        PSLL<int> *test_psll_31 = new PSLL<int>; //Declare a new list
        *test_psll_31 = *test_psll_30; //Copy the list using a copy assignment operator

        //By doing the following operations with both lists we prove that we did a deep copy of the original list

        //Original list
        REQUIRE(test_psll_30->length() == 66);
        REQUIRE(!test_psll_30->is_empty());
        REQUIRE(!test_psll_30->is_full());
        REQUIRE(test_psll_30->replace(99, 15) == 15);
        REQUIRE(test_psll_30->item_at(15) == 99);
        REQUIRE(test_psll_30->remove(14) == 14);
        test_psll_30->insert(14, 14);
        REQUIRE(test_psll_30->peek_front() == 0);
        REQUIRE(test_psll_30->pop_front() == 0);
        REQUIRE(test_psll_30->peek_back() == 65);
        REQUIRE(test_psll_30->pop_back() == 65);
        REQUIRE(test_psll_30->item_at(14) == 99);
        REQUIRE(test_psll_30->contains(99, equals_function) == 1);
        std::ostringstream dtream;
        test_psll_30->print(dtream);
        REQUIRE(dtream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64]");

        //Copied list
        REQUIRE(test_psll_31->length() == 66);
        REQUIRE(!test_psll_31->is_empty());
        REQUIRE(!test_psll_31->is_full());
        REQUIRE(test_psll_31->replace(99, 15) == 15);
        REQUIRE(test_psll_31->item_at(15) == 99);
        REQUIRE(test_psll_31->remove(14) == 14);
        test_psll_31->insert(14, 14);
        REQUIRE(test_psll_31->peek_front() == 0);
        REQUIRE(test_psll_31->pop_front() == 0);
        REQUIRE(test_psll_31->peek_back() == 65);
        REQUIRE(test_psll_31->pop_back() == 65);
        REQUIRE(test_psll_31->item_at(14) == 99);
        REQUIRE(test_psll_31->contains(99, equals_function) == 1);
        std::ostringstream btream;
        test_psll_31->print(btream);
        REQUIRE(btream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64]");

        delete test_psll_31;
        delete test_psll_30;
    }

    SECTION("Testing move assignment operator") {
        PSLL<int> *test_psll_32 = new PSLL<int>;
        ;
        for (int i = 65; i >= 0; i--) {
            if (!(i % 2)) test_psll_32->push_front(i);
            else test_psll_32->push_front(i);
        }

        PSLL<int> *test_psll_33 = new PSLL<int>; //Declare a new list
        *test_psll_33 = std::move(*test_psll_32); //Use the move assignment operator to "move" the original list into the new list

        REQUIRE(test_psll_32->length() == 0); //This line guarantees that the original list was cleared

        //The following lines of code proof that the created list is equivalent to the original list before the move operation
        REQUIRE(test_psll_33->length() == 66);
        REQUIRE(!test_psll_33->is_empty());
        REQUIRE(!test_psll_33->is_full());
        REQUIRE(test_psll_33->replace(99, 15) == 15);
        REQUIRE(test_psll_33->item_at(15) == 99);
        REQUIRE(test_psll_33->remove(14) == 14);
        test_psll_33->insert(14, 14);
        REQUIRE(test_psll_33->peek_front() == 0);
        REQUIRE(test_psll_33->pop_front() == 0);
        REQUIRE(test_psll_33->peek_back() == 65);
        REQUIRE(test_psll_33->pop_back() == 65);
        REQUIRE(test_psll_33->item_at(14) == 99);
        REQUIRE(test_psll_33->contains(99, equals_function) == 1);
        std::ostringstream dtream;
        test_psll_33->print(dtream);
        REQUIRE(dtream.str() == "[1,2,3,4,5,6,7,8,9,10,11,12,13,14,99,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64]");

        delete test_psll_33;
        delete test_psll_32;
    }

}
