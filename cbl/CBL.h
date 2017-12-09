// Circular Buffer List
// Similar to an SDAL, except that the backing array is treated like a circular buffer when inserting-at/removing-from the head. 
// It shall thus have the data members head and tail. The policy for when and how to grow/shrink the backing array is the same as with SDAL.
// A basic implementation: the initial array size is passed as a parameter to the constructor; if no value is passed then default to a backing array with 50 slots. 
// Whenever an item is added and the backing array is full, allocate a new array 150% the size of the original, copy the items over to the new array,
// and deallocate the original one.
// Because we don't want the list to waste too much memory, whenever the array's size is ≥ twice the starting capacity and fewer than half the slots are used, 
// allocate a new array 75% the size of the current array, copy the items over to the new array, deallocate the current array, and use the new array as the backing store.
// by Iago Patiño López
// with content from https://www.cise.ufl.edu/~dts/ as well as "Algorithms in C++ by Robert Segewick"

#ifndef CBAL_H
#define CBAL_H
#include <stdexcept>
#include <iostream>
#include "List.h"

namespace cop3530 {

    template <typename E>
    class CBL : public List<E> { //We need to create the list class

    public:

        template <typename T>
        class CBAL_Iter {
        public:
            // type aliases required for C++ iterator compatibility
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            // type aliases for prettier code
            using self_type = CBAL_Iter;
            using self_reference = CBAL_Iter&;

        private:
            E* here; //This is the pointer the the list member the iterator is pointing at

        public:

            explicit CBAL_Iter(E *start = nullptr) : here(start) { //This is the explicit constructor for the iterator class. It does not allow implicit conversions or copy-initialization.
            }

            CBAL_Iter(const CBAL_Iter& src) : here(src.here) { //This is the regular constructor for the iterator class
            }

            reference operator*() const {
                return *here; //temporary line
            }

            pointer operator->() const {
                T *temp = here;
                return temp;
            }

            self_reference operator=(CBAL_Iter<T> const& src) {
                here = CBAL_Iter(src).here;
                return *this;
            }

            self_reference operator++() { //Returns the modified iterator
                here++;
                return *this;
            } // preincrement

            self_type operator++(int) {
                CBAL_Iter temp(*this);
                here++;
                return temp;
            } // postincrement

            bool operator==(CBAL_Iter<T> const& rhs) const {
                if (here == rhs.here)
                    return true;
                else
                    return false;
            }

            bool operator!=(CBAL_Iter<T> const& rhs) const {
                if (here != rhs.here)
                    return true;
                else
                    return false;
            }

        }; // end CBAL_Iter        

        using size_t = std::size_t; // you may comment out this line if your compiler complains
        using value_type = E;
        using iterator = CBAL_Iter<E>; //When we use the word iterator, we mean the iterator class
        using const_iterator = CBAL_Iter<E const>;

        //operations
        CBL(int); //This is the constructor method with input 
        CBL(); //This is the constructor method without input
        CBL(const CBL& other); //copy constructor
        CBL(CBL&& other); //move constructor
        ~CBL(); //This is the destructor method of the singly linked list

        iterator begin() {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return CBAL_Iter<E>(&array[head]);
        }

        iterator end() {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return CBAL_Iter<E>(&array[tail]);
        }

        const_iterator begin() const {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return CBAL_Iter<E>(&array[head]);
        }

        const_iterator end() const {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return CBAL_Iter<E>(&array[tail]);
        }
        CBL & operator=(const CBL & other);
        CBL & operator=(CBL&& other);
        void insert(E element, int); //Adds the specific element to the list at the specified position, shifting the element originally at that and those in subsequent positions one position to the "right"
        void push_back(E element); //Appends the specified element to the list
        void push_front(E element); //Prepends the specified element to the list
        E replace(E element, int); //Replaces the existing element at the specified position with the specified element and returns the original element
        E remove(int); //Removes and returns the element at the specified position, shifting the subsequent elements one position to the "left"
        E pop_back(void); //Removes and returns the element at the list's tail
        E pop_front(void); //Removes and returns the element at the list's head
        E item_at(int); //Returns (without removing from the list) the element at the specified position
        E peek_back(void); //Returns the elements at the list's tail
        E peek_front(void); //Returns the elements at the list's head
        bool is_empty(void); //Returns true IFF the list contains no elements
        bool is_full(void);
        size_t length(void); //Returns the number of elements in the list as a size_t
        void clear(void); //removes all elements from the list
        bool contains(E element, bool (*equals_function)(const E&, const E&)); //returns true IFF at least one of the elements of the list matches the specified element
        void print(std::ostream& o); //If the list is empty, inserts "<empty list>" into the ostream; otherwise, inserts, enclosed in square brackets, the list's elements, separated by commas, in sequential order 

        E * const contents(); //Allocates, initializes, and returns an array containing a copy of the list's elements in sequential order

    private:
        void upsize(void);
        void adjust_size(void);
        //variables
        size_t size; //This is size of the backing array of the Circular Buffer List
        size_t original_size;
        E *array; //This is the backing array of the Circular Buffer List
        int head; //The head data member gives you the index at which the head of the list it.
        int tail; //The tail data member gives you the index after which the last element of the list is.
    };

    //==============================================================================
    // ------- constructor  --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    CBL<E>::CBL(int input) {
        size = input;
        original_size = input;
        array = new E[size];
        head = 0; //We start with an empty list, which be define as head==tail.  
        tail = 0;
    }

    //==============================================================================
    // ------- constructor 2 --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    CBL<E>::CBL() {
        size = 50;
        original_size = size;
        array = new E[size];
        head = 0;
        tail = 0;
    }

    //==============================================================================
    // ------- copy constructor  --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    CBL<E>::CBL(const CBL& other) {
        size = other.size;
        original_size = other.original_size;
        array = new E[size];
        head = 0;

        if (other.head > other.tail) {
            int index_array = other.head; //Read old array starting at head
            int index_new_array = 0; //Write new array starting at 0
            while (index_array < other.size)//Copy from head to the end of the old array
                array[index_new_array++] = other.array[index_array++];
            if (other.tail > 0) index_array = 0;
            while (index_array < other.tail) {//Copy from the beginning of the old array to the tail 
                array[index_new_array++] = other.array[index_array++];
            }
            tail = index_new_array;

        } else { //If our list does not circle the array
            int index_array = other.head; //Read old array starting at head
            int index_new_array = 0; //Write new array starting at 0
            while (index_array < other.tail)
                array[index_new_array++] = other.array[index_array++];
            tail = index_new_array;
        }
    }

    //==============================================================================
    // ------- copy-assignment operator 

    template <typename E>
    CBL<E> &
    CBL<E>::operator=(const CBL & other) {
        size = other.size;
        original_size = other.original_size;
        array = new E[size];
        head = 0;

        if (other.head > other.tail) {
            int index_array = other.head; //Read old array starting at head
            int index_new_array = 0; //Write new array starting at 0
            while (index_array < other.size)//Copy from head to the end of the old array
                array[index_new_array++] = other.array[index_array++];
            if (other.tail > 0) index_array = 0;
            while (index_array < other.tail) {//Copy from the beginning of the old array to the tail 
                array[index_new_array++] = other.array[index_array++];
            }
            tail = index_new_array;

        } else { //If our list does not circle the array
            int index_array = other.head; //Read old array starting at head
            int index_new_array = 0; //Write new array starting at 0
            while (index_array < other.tail)
                array[index_new_array++] = other.array[index_array++];
            tail = index_new_array;
        }

        return *this;
    }

    // ------  move constructor

    template <typename E>
    CBL<E>::CBL(CBL&& other) {
        array = other.array;
        size = other.size;
        original_size = other.original_size;
        head = other.head;
        tail = other.tail;

        other.size = 50;
        other.original_size = other.size;
        other.array = new E[size];
        other.head = 0;
        other.tail = 0;
    }
    // ------- move assignment operator 

    template <typename E>
    CBL<E> &
    CBL<E>::operator=(CBL&& other) {
        if (this != &other) {
        array = other.array;
        size = other.size;
        original_size = other.original_size;
        head = other.head;
        tail = other.tail;

        other.size = 50;
        other.original_size = other.size;
        other.array = new E[size];
        other.head = 0;
        other.tail = 0;
        }
        return *this;
    }
    // ------  destructor --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    CBL<E>::~CBL() {
        delete [] array;
    }

    //==============================================================================
    // operations

    //==============================================================================
    // --------- upsize() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CBL<E>::upsize() { //We use this to increase our backing array size by 50&

        size_t new_array_size = size * 1.5; //The new array has to be 150% of the previous array

        E *new_array = new E[new_array_size]; //Create new bigger array
        //If our list circles the array
        if (head > tail) {

            int index_array = head; //Read old array starting at head
            int index_new_array = 0; //Write new array starting at 0
            while (index_array < size)//Copy from head to the end of the old array
                new_array[index_new_array++] = array[index_array++];
            if (tail > 0) index_array = 0;
            while (index_array < tail) {//Copy from the beginning of the old array to the tail 

                new_array[index_new_array++] = array[index_array++];
            }
            this->tail = index_new_array;
            this->head = 0;
            delete array;
            array = new_array;
            size = new_array_size;
            return;
        }

        //If our list does not circle the array
        int index_array = head;
        int index_new_array = 0;
        while (index_array < tail)
            new_array[index_new_array++] = array[index_array++];
        tail = index_array;
        head = 0;
        delete array;
        array = new_array;
        size = new_array_size;
    }

    //==============================================================================
    // --------- adjust_size() ----------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CBL<E>::adjust_size() {
        if (size < 2 * original_size) return; //If the array's size is not larger than or equal to the original array the condition for downsizing is not met.
        if (this->length() >= size / 2) return; //If more than half of the slots in the backing array are being used, the condition for downsizing is not met.

        //Once the conditions have been met, we can downsize the array.
        size_t new_array_size = size * 0.75;
        E *new_array = new E[new_array_size];

        //If our list circles the array
        if (head > tail) {
            int index_array = head;
            int index_new_array = 0;
            while (index_array < size)//Copy from head to the end of the array
                new_array[index_new_array++] = array[index_array++];
            index_array = 0;
            while (index_array < tail)//Copy from the beginning of the array to the tail 
                new_array[index_new_array++] = array[index_array++];
            tail = index_array;
            head = 0;
            delete array;
            array = new_array;
            size = new_array_size;
            return;
        }
        //If our list does not circle the array
        int index_array = head;
        int index_new_array = 0;
        while (index_array < tail)
            new_array[index_new_array++] = array[index_array++];
        tail = index_array;
        head = 0;
        delete array;
        array = new_array;
        size = new_array_size;
    }

    //==============================================================================
    // --------- insert() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CBL<E>::insert(E element, int position) {
        if (position > length() || position < 0) throw std::runtime_error("Sorry, you cannot insert outside the list boundaries");
        if (position == length()){
            this->push_back(element);
            return;
        }
        else if (tail < size - 1 && tail + 1 != head) { //If there is space for increase
            tail++;
            size_t real_position = position + head;
            if (real_position >= size)
                real_position = real_position - size;
            if (head < tail) { //If the array does not circle
                for (int i = tail; i > real_position; i--)
                    array[i] = array[i - 1];
                array[real_position] = element;
            } else if (head > tail && head < real_position) { //If the array circles but the insert position is after the head
                for (int i = tail - 1; i >= 0; i--)
                    array[i] = array[i - 1];
                array[0] = array[size - 1];
                for (int i = size - 1; i >= real_position; i--)
                    array[i] = array[i - 1];
                array[real_position] = element;
            } else if (head > tail && head > real_position) { //If the array circles put the insert position is before the tail
                for (int i = tail; i > real_position; i--)
                    array[i] = array[i - 1];
                array[real_position] = element;
            }

        } else { //If there is no space for increase
            upsize();
            insert(element, position); //Let's try again
        }
    }

    //==============================================================================
    // --------- contents() --------------------------------------------------------------------------------- IT WORKS


    template <typename E >
    E * const
    CBL<E>::contents() {
        E * const new_array = new E[length()];
        if (head > tail) { //If the array circles
            int index_array = head; //Read old array starting at head
            int index_new_array = 0; //Write new array starting at 0
            while (index_array < size)//Copy from head to the end of the old array
                new_array[index_new_array++] = array[index_array++];
            if (tail > 0) index_array = 0;
            while (index_array < tail) {//Copy from the beginning of the old array to the tail 
                new_array[index_new_array++] = array[index_array++];
            }
            return new_array;
        }
        //If our list does not circle the array
        int index_array = head;
        int index_new_array = 0;
        while (index_array < tail)
            new_array[index_new_array++] = array[index_array++];
        return new_array;
    }


    //==============================================================================
    // --------- push_back() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CBL<E>::push_back(E element) {
        if (tail + 1 == head) this->upsize();
        if (tail == size - 1 && head == 0) this->upsize();
        array[tail++] = element;
        if (tail >= size) tail = 0;
    }

    //==============================================================================
    // --------- push_front() ------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CBL<E>::push_front(E element) {
        if (tail + 1 == head) this->upsize();
        if (tail == size - 1 && head == 0) this->upsize();
        if (head == 0) head = size;
        array[--head] = element;
    }

    //==============================================================================
    // --------- replace() ---------------------------------------------------------------------------------- IT WORKS

    template <typename E >
    E
    CBL<E>::replace(E element, int position) {
        if (position >= this->length() || this->is_empty()) throw std::runtime_error("Sorry, but that position is outside the list boundaries");
        size_t real_position = position + head;
        if (real_position >= size)
            real_position = real_position - size;
        E temp = array[real_position];
        array[real_position] = element;
        return temp;
    }

    //==============================================================================
    // --------- remove() --------------------------------------------------------------------------------- IT WORKS

    template <typename E >
    E
    CBL<E>::remove(int position) {
        if (position > length() - 1 || position < 0)
            throw std::runtime_error("Error from remove method: the position chosen is not in the list");
        if (position == 0) return this->pop_front();
        size_t real_position = position + head;
        if (real_position >= size)
            real_position = real_position - size;
        E removed = array[real_position];
        //If our list does not circle the array
        if (tail > head) {
            for (int i = real_position; i < tail; i++)
                array[i] = array[i + 1];
            tail--;
        }//If our list circles the array
        else if (tail < head && head < real_position) {
            for (int i = real_position; i < size - 1; i++)
                array[i] = array[i + 1];
            array[size - 1] = array[0];
            for (int i = 0; i < tail - 1; i++)
                array[i] = array[i + 1];
            tail--;
        } else if (tail < head && head > real_position) {
            for (int i = real_position; i < tail - 1; i++)
                array[i] = array[i + 1];
            tail--;
        }
        this->adjust_size();
        return removed;
    }

    //==============================================================================
    // --------- pop_back() --------------------------------------------------------------------------------- IT WORKS

    template <typename E >
    E
    CBL<E>::pop_back() {
        if (this->is_empty()) throw std::runtime_error("Sorry, but this list is empty");
        E temp = array[--tail];
        if (tail == -1) {
            temp = array[size - 1];
            tail = size - 1;
        }
        this->adjust_size();
        return temp;
    }

    //==============================================================================
    // --------- pop_front() --------------------------------------------------------------------------------- IT WORKS

    template <typename E >
    E
    CBL<E>::pop_front() {
        if (this->is_empty()) throw std::runtime_error("Sorry, but this list is empty");
        if (head == size - 1) {
            E removed = array[head];
            head = 0;
            return removed;
        }
        E removed = array[head++];
        return removed;
    }

    //==============================================================================
    // --------- item_at() --------------------------------------------------------------------------------- IT WORKS

    template <typename E >
    E
    CBL<E>::item_at(int position) {
        if (position >= this->length() || this->is_empty()) throw std::runtime_error("Sorry, but that position is outside the list boundaries");
        size_t real_position = position + head;
        if (real_position >= size)
            real_position = real_position - size;
        return array[real_position];
    }

    //==============================================================================
    // --------- peek_back() --------------------------------------------------------------------------------- IT WORKS

    template <typename E >
    E
    CBL<E>::peek_back() {
        if (is_empty()) throw std::runtime_error("This list is empty");
        if (tail == 0) return array[size - 1];
        return array[tail - 1];
    }

    //==============================================================================
    // --------- peek_front() --------------------------------------------------------------------------------- IT WORKS

    template <typename E >
    E
    CBL<E>::peek_front() {
        if (is_empty()) throw std::runtime_error("This list is empty");
        return array[head];
    }

    //==============================================================================
    // --------- is_empty() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    CBL<E>::is_empty() {
        return head == tail;
    }

    //==============================================================================
    // --------- is_full() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    CBL<E>::is_full(void) {
        return false; //This list can have an infinite amount of nodes and therefore it always returns false 
    }

    //==============================================================================
    // --------- length() --------------------------------------------------------------------------------- IT WORKS

    template <typename E >
    size_t
    CBL<E>::length() {
        if (is_empty()) return 0;
        if (tail < head) return size - head + tail;
        return tail - head;
    }

    //==============================================================================
    // --------- clear() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CBL<E>::clear() {
        head = 0;
        tail = 0;
    }

    //==============================================================================
    // --------- contains() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    CBL<E>::contains(E element, bool (*equals_function)(const E&, const E&)) {
        if (is_empty()) return false;
        //If our list circles the array
        if (head > tail) {
            int index = head;
            while (index < size) //Examine from head to the end of the array
                if (equals_function(array[index++], element)) return true;
            index = 0;
            while (index < tail) //Examine from the beginning of the array to the tail 
                if (equals_function(array[index++], element)) return true;
        }
        //If our list does not circle the array
        int index = head;
        while (index < (tail))
            if (equals_function(array[index++], element)) return true;
        return false;
    }

    //==============================================================================
    // --------- print() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CBL<E>::print(std::ostream & o) {
        if (is_empty()) {
            o << "<empty list>" << std::endl;
            return;
        }

        //If our list circles the array but tail is 0
        if (head > tail && tail == 0) {
            int index = head;
            o << "[";
            while (index < size - 1)//Print from head to the end of the array
                o << array[index++] << ",";
            o << array[index] << "]";
            return;
        }
        //If our list circles the array
        if (head > tail) {
            int index = head;
            o << "[";
            while (index < size)//Print from head to the end of the array
                o << array[index++] << ",";
            index = 0;
            while (index < (tail - 1))//Print from the beginning of the array to the tail 
                o << array[index++] << ",";
            o << array[index] << "]";
            return;
        }

        //If our list does not circle the array
        int index = head;
        o << "[";
        while (index < (tail - 1))

            o << array[index++] << ",";
        o << array[index] << "]";
    }
}



#endif /* CBAL_H */

