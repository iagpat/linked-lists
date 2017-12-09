//Simple Dynamic Array-based List (SDAL)
//A basic implementation: the initial array size is passed as a parameter to the constructor; if no value is passed then default to a backing array with 50 slots. Whenever an item is added and the backing array is full, allocate a new array 150% the size of the original, copy the items over to the new array, and deallocate the original one.
//Because we don't want the list to waste too much memory, whenever the array's size is ≥ twice the starting capacity and fewer than half the slots are used, allocate a new array 75% the size of the current array, copy the items over to the new array, and deallocate the current array, and use the new array as the backing store.
// by Iago Patiño López
// with content from https://www.cise.ufl.edu/~dts/ as well as "Algorithms in C++ by Robert Segewick"

#ifndef SDAL_H
#define SDAL_H
#include <stdexcept>
#include <iostream>
#include "List.h"

namespace cop3530 {

    template <typename E>
    class SDAL : public List<E> { //We need to create the list class

    public:

        template <typename T>
        class SDAL_Iter {
        public:
            // type aliases required for C++ iterator compatibility
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            // type aliases for prettier code
            using self_type = SDAL_Iter;
            using self_reference = SDAL_Iter&;

        private:
            E* here; //This is the pointer the the list member the iterator is pointing at

        public:

            explicit SDAL_Iter(E *start = nullptr) : here(start) { //This is the explicit constructor for the iterator class. It does not allow implicit conversions or copy-initialization.
            }

            SDAL_Iter(const SDAL_Iter& src) : here(src.here) { //This is the regular constructor for the iterator class
            }

            reference operator*() const {
                return *here; //temporary line
            }

            pointer operator->() const {
                T *temp = here;
                return temp;
            }

            self_reference operator=(SDAL_Iter<T> const& src) {
                here = SDAL_Iter(src).here;
                return *this; //temporary line
            }

            self_reference operator++() { //Returns the modified iterator
                here = here + 1;
                return *this;
            } // preincrement

            self_type operator++(int) {
                SDAL_Iter temp(*this);
                here = here + 1;
                return temp;
            } // postincrement

            bool operator==(SDAL_Iter<T> const& rhs) const {
                if (here == rhs.here)
                    return true;
                else
                    return false;
            }

            bool operator!=(SDAL_Iter<T> const& rhs) const {
                if (here != rhs.here)
                    return true;
                else
                    return false;
            }

        }; // end SDAL_Iter        

        using size_t = std::size_t; // you may comment out this line if your compiler complains
        using value_type = E;
        using iterator = SDAL_Iter<E>; //When we use the word iterator, we mean the iterator class
        using const_iterator = SDAL_Iter<E const>;

        //operations
        SDAL(int); //This is the constructor method with input 
        SDAL(); //This is the constructor method without input
        SDAL(const SDAL& other); //copy constructor
        SDAL(SDAL&& other); //move constructor
        ~SDAL(); //This is the destructor method of the singly linked list

        iterator begin() {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return SDAL_Iter<E>(array);
        }

        iterator end() {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return SDAL_Iter<E>(&array[tail]);
        }

        const_iterator begin() const {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return SDAL_Iter<E>(array);
        }

        const_iterator end() const {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return SDAL_Iter<E>(array[tail]);
        }
        SDAL & operator=(const SDAL & other);
        SDAL & operator=(SDAL&& other);
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
        size_t size;
        size_t starting_size;
        E *array;
        //E *tail;
        int tail;
    };

    //==============================================================================
    // ------- constructor  

    template <typename E>
    SDAL<E>::SDAL(int input) {
        size = input;
        starting_size = size;
        array = new E[size];
        tail = 0;
    }

    //==============================================================================
    // ------- constructor 2 

    template <typename E>
    SDAL<E>::SDAL() {
        size = 50;
        starting_size = size;
        array = new E[size];
        tail = 0;
    }

    //==============================================================================
    // ------- copy constructor 

    template <typename E>
    SDAL<E>::SDAL(const SDAL& other) {
        size = other.size; //Copy the size of the array
        starting_size = other.starting_size; //Copy the starting size
        array = new E[size];
        
        for (int i = 0; i<other.tail; i++){
            array[i] = other.array[i];
            tail = i;
        }
        tail++;
    }

    // ------- copy-assignment operator 

    template <typename E>
    SDAL<E> &
    SDAL<E>::operator=(const SDAL & other) {
        
        size = other.size; //Copy the size of the array
        starting_size = other.starting_size; //Copy the starting size
        array = new E[size];
                for (int i = 0; i<other.tail; i++){
            array[i] = other.array[i];
            tail = i;
        }
        tail++;
        return *this;
    }

    // ------  move constructor

    template <typename E>
    SDAL<E>::SDAL(SDAL&& other) {
        //Soft copy old list
        array = other.array;
        tail = other.tail;
        size = other.size;
        starting_size = other.starting_size;

        //Reset old list
        other.array = new E[size];
        other.tail = 0;
        other.size = 50;
        other.starting_size = 50;

    }
    // ------- move assignment operator 

    template <typename E>
    SDAL<E> &
    SDAL<E>::operator=(SDAL&& other) {
        
        if (this != &other) {
            this->clear();
            //Soft copy old list
            array = other.array;
            tail = other.tail;
            size = other.size;
            starting_size = other.starting_size;

            //Reset old list
            other.array = new E[size];
            other.tail = 0;
            other.size = 50;
            other.starting_size = 50;
        }
        return *this;
    }

    // ------  destructor 

    template <typename E>
    SDAL<E>::~SDAL() {
        delete [] array;
    }

    //==============================================================================
    // operations

    //==============================================================================
    // --------- upsize() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    SDAL<E>::upsize() {
        size_t previous_size = size;
        size = size * 1.5;
        E *temp_array = new E[size];
        for (int i = 0; i < previous_size; i++) {
            temp_array[i] = array[i];
        }
        delete [] array;
        array = &temp_array[0];
        tail = previous_size;
    }

    //==============================================================================
    // --------- adjust_size() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    SDAL<E>::adjust_size() {
        if (size >= 2 * starting_size && length() < size / 2) {
            size_t previous_size = size;
            size = size * 0.75;
            E *temp_array = new E[size];
            for (int i = 0; i < previous_size; i++) {
                temp_array[i] = array[i];
            }
            delete [] array;
            array = &temp_array[0];
            tail = previous_size;
        }
    }

    //==============================================================================
    // --------- insert() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    SDAL<E>::insert(E element, int position) {
        if (position > length() || position < 0) throw std::runtime_error("Sorry, you cannot insert outside the list boundaries");
        if (tail != size){    
            tail++;
            for (int i = length(); i > position; i--)
                array[i] = array[i - 1];
            array[position] = element;
        } else if (tail == size){    
            upsize();
            insert(element, position);
        }
    }

    //==============================================================================


    template <typename E>
    E * const
    SDAL<E>::contents() {
        E * const newarray = new E[length()];
        int index_array = 0;
        int index_new_array = 0;
        while (index_array < tail)
            newarray[index_new_array++] = array[index_array++];
        return newarray;
    }


    //==============================================================================
    // --------- push_back() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    SDAL<E>::push_back(E element) {
        if (tail != size){    
            array[tail++] = element;
        }else if (tail == size) {    
            upsize();
            push_back(element);
        }
    }

    //==============================================================================
    // --------- push_front() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    SDAL<E>::push_front(E element) {
         if (tail != size){    
            for (int i = length(); i > 0; i--)
                array[i] = array[i - 1];
            array[0] = element;
            tail++;
         }else if (tail == size){    
            upsize();
            push_front(element);
        }
    }

    //==============================================================================
    // --------- replace() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    SDAL<E>::replace(E element, int position) {
        if (position > length() - 1 || position < 0) throw std::runtime_error("Error from replace method: the position chosen is not in the list");
        E displaced = array[position];
        array[position] = element;
        return displaced;
    }

    //==============================================================================
    // --------- remove() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    SDAL<E>::remove(int position) {
        if (position > length() - 1 || position < 0)
            throw std::runtime_error("Error from remove method: the position chosen is not in the list");
        E removed = array[position];
        for (int i = position; i < length(); i++)
            array[i] = array[i + 1];
        tail--;
        adjust_size();
        return removed;
    }

    //==============================================================================
    // --------- pop_back() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    SDAL<E>::pop_back() {
        if (is_empty())
            throw std::runtime_error("Error in the pop back method, the list is empty");
        E removed = array[tail-1];
        tail--;
        adjust_size();
        return removed;
    }

    //==============================================================================
    // --------- pop_front() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    SDAL<E>::pop_front() {
        if (is_empty()) throw std::runtime_error("Error in the pop front method, the list is empty");
        E removed = array[0];
        for (int i = 0; i < length(); i++)
            array[i] = array[i + 1];
        tail--;
        adjust_size();
        return removed;
    }

    //==============================================================================
    // --------- item_at() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    SDAL<E>::item_at(int position) {
        if (position > length() - 1 || position < 0) throw std::runtime_error("Error from item at method: the position chosen is not in the list");
        return array[position];
    }

    //==============================================================================
    // --------- peek_back() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    SDAL<E>::peek_back() {
        if (is_empty()) throw std::runtime_error("Error in the peek back method, the list is empty");
        return array[tail-1];
    }

    //==============================================================================
    // --------- peek_front() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    SDAL<E>::peek_front() {
        if (is_empty()) throw std::runtime_error("Error in the peek front method, the list is empty");
        return array[0];
    }

    //==============================================================================
    // --------- is_empty() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    SDAL<E>::is_empty() {
        return tail == 0;
    }

    //==============================================================================
    // --------- is_full() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    SDAL<E>::is_full(void) {
        return false; //This list can have an infinite amount of nodes and therefore it always returns false 
    }

    //==============================================================================
    // --------- length() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    size_t
    SDAL<E>::length() {
        return tail;
    }

    //==============================================================================
    // --------- clear() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    SDAL<E>::clear() {
        tail = 0;
        adjust_size();
    }

    //==============================================================================
    // --------- contains() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    SDAL<E>::contains(E element, bool (*equals_function)(const E&, const E&)) {
        if (is_empty()) return false;
        for (int i = 0; i<tail; i++)
              if (equals_function(array[i], element)) return true;
        return false;
    }

    //==============================================================================
    // --------- print() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    SDAL<E>::print(std::ostream& o) {
        if (is_empty()) {
            o << "<empty list>" << std::endl;
            return;
        }
        
        o << "[";
        for (int i = 0; i<tail-1; i++){
          o << array[i]<<",";
        }
        o << array[tail-1]<< "]";
    }
}
#endif /* SDAL_H */



