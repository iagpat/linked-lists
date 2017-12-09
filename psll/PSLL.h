//Simple Singly-Linked List (PSLL)
// Similar to the SSLL, except the node allocation/deallocation strategy is different. The list maintains a pool of unused nodes. Whenever an item is added to the list, use a node from the pool of free nodes; if there are no free nodes, then a new node is allocated. Whenever an item is removed, the node is added to the pool.
//Because we don't want the pool to waste too much memory, whenever the list contains ≥ 100 items AND the pool contains more nodes than half the list size, reduce the number of pool nodes to half the list size (by deallocating the excess).
//
// by Iago Patiño López
// with content from https://www.cise.ufl.edu/~dts/ as well as "Algorithms in C++ by Robert Segewick"

#ifndef PSLL_H
#define PSLL_H
#include <stdexcept>
#include <iostream>
#include "List.h"


namespace cop3530 {

    template <typename E>
    class PSLL : public List<E> { //We need to create the list class

    public:

        template <typename T>
        class PSLL_Iter {
        public:
            // type aliases required for C++ iterator compatibility
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            // type aliases for prettier code
            using self_type = PSLL_Iter;
            using self_reference = PSLL_Iter&;

        private:
            node<T>* here; //This is the pointer the the list member the iterator is pointing at

        public:

            explicit PSLL_Iter(node<T>* start = nullptr) : here(start) { //This is the explicit constructor for the iterator class. It does not allow implicit conversions or copy-initialization.
            }

            PSLL_Iter(const PSLL_Iter& src) : here(src.here) { //This is the regular constructor for the iterator class
            }

            reference operator*() const {
                return here->datum; //temporary line
            }

            pointer operator->() const {
                return &(here->datum);
            }

            self_reference operator=(PSLL_Iter<T> const& src) {
                here = PSLL_Iter(src).here;
                return *this; //temporary line
            }

            self_reference operator++() { //Returns the modified iterator
                here = here->next;
                return *this;
            } // preincrement

            self_type operator++(int) {
                PSLL_Iter temp(*this);
                here = here->next;
                return temp;
            } // postincrement

            bool operator==(PSLL_Iter<T> const& rhs) const {
                if (here == rhs.here) return true;
                return false;
            }

            bool operator!=(PSLL_Iter<T> const& rhs) const {
                if (here != rhs.here) return true;
                return false;
            }

        }; // end SSLL_Iter        

        using size_t = std::size_t; // you may comment out this line if your compiler complains
        using value_type = E;
        using iterator = PSLL_Iter<E>; //When we use the word iterator, we mean the iterator class
        using const_iterator = PSLL_Iter<E const>;
        //operations
        PSLL(); //This is the constructor method of the singly linked list
        PSLL(const PSLL& other); //copy constructor
        PSLL(PSLL&& other); //move constructor
        ~PSLL(); //This is the destructor method of the singly linked list

        iterator begin() {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return PSLL_Iter<E>(head);
        }

        iterator end() {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return PSLL_Iter<E>(tail->next);
        }

        const_iterator begin() const {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return PSLL_Iter<E>(head);
        }

        const_iterator end() const {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return PSLL_Iter<E>(tail->next);
        }
        PSLL & operator=(const PSLL & other);
        PSLL & operator=(PSLL&& other);
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
        bool is_full(void); //There isn't a is_full method because a PSLL cannot be full
        size_t length(void); //Returns the number of elements in the list as a size_t
        void clear(void); //removes all elements from the list
        bool contains(E element, bool (*equals_function)(const E&, const E&)); //returns true IFF at least one of the elements of the list matches the specified element
        void print(std::ostream& o); //If the list is empty, inserts "<empty list>" into the ostream; otherwise, inserts, enclosed in square brackets, the list's elements, separated by commas, in sequential order 


        E * const contents(); //Allocates, initializes, and returns an array containing a copy of the list's elements in sequential order

    private:
        void psll_rules_check(void);
        //variables
        node<E> *head;
        node<E> *tail;
        node<E> *poolhead;
        node<E> *pooltail;
        int poolcount;
    };

    //==============================================================================
    // ------- constructor  

    template <typename E>
    PSLL<E>::PSLL() {
        head = nullptr;
        tail = nullptr;
        poolcount = 0;

        pooltail = nullptr;
        poolhead = nullptr;
    }
    // ------- copy constructor 

    template <typename E>
    PSLL<E>::PSLL(const PSLL& other) {
        //First copy the head
        head = new node<E>;
        head->datum = other.head->datum;

        //Traversal pointers
        node<E> *new_nodes = head;
        node<E> *old_nodes = other.head;

        //Deep copy
        while (old_nodes->next) { //While we have not finished traversing the "old" chain
            new_nodes->next = new node<E>;
            new_nodes = new_nodes->next;
            old_nodes = old_nodes->next;
            new_nodes->datum = old_nodes->datum;
        }

        //Copy the tail
        tail = new_nodes;
        tail->next = nullptr;

        //Set pool
        poolcount = 0;
        pooltail = nullptr;
        poolhead = nullptr;

    }

    // ------- copy-assignment operator 

    template <typename E>
    PSLL<E> &
    PSLL<E>::operator=(const PSLL & other) {
        //First copy the head
        head = new node<E>;
        head->datum = other.head->datum;

        //Traversal pointers
        node<E> *new_nodes = head;
        node<E> *old_nodes = other.head;

        //Deep copy
        while (old_nodes->next) { //While we have not finished traversing the "old" chain
            new_nodes->next = new node<E>;
            new_nodes = new_nodes->next;
            old_nodes = old_nodes->next;
            new_nodes->datum = old_nodes->datum;
        }

        //Copy the tail
        tail = new_nodes;
        tail->next = nullptr;

        //Set pool
        poolcount = 0;
        pooltail = nullptr;
        poolhead = nullptr;

        return *this;
    }
    // ------  move constructor

    template <typename E>
    PSLL<E>::PSLL(PSLL&& other) {
        head = other.head;
        tail = other.tail;
        poolhead = other.poolhead;
        pooltail = other.pooltail;
        poolcount = other.poolcount;

        other.head = nullptr;
        other.tail = nullptr;
        other.poolhead = nullptr;
        other.pooltail = nullptr;
        poolcount = 0;
    }
    // ------- move assignment operator 

    template <typename E>
    PSLL<E> &
    PSLL<E>::operator=(PSLL&& other) {
        if (this != &other) {
            this->clear();
            head = other.head;
            tail = other.tail;
            poolhead = other.poolhead;
            pooltail = other.pooltail;
            poolcount = other.poolcount;

            other.head = nullptr;
            other.tail = nullptr;
            other.poolhead = nullptr;
            other.pooltail = nullptr;
            poolcount = 0;
        }
        return *this;
    }
    // ------  destructor 

    template <typename E>
    PSLL<E>::~PSLL() {
        clear();
        while (poolcount > 0) //This deletes every element of the list except for the tail
        {
            node<E> *eliminate = poolhead;
            poolhead = poolhead->next;
            delete eliminate;
            poolcount--;
        }

    }

    //==============================================================================
    // operations
    //==============================================================================
    // --------- psll_rules_check() Because we don't want the pool to waste too much memory, whenever the list contains ≥ 100 items AND the pool contains more nodes than half the list size, reduce the number of pool nodes to half the list size (by deallocating the excess).

    template <typename E>
    void
    PSLL<E>::psll_rules_check() {
        if (poolcount > 50) {
            int nodes_to_delete = 50 - poolcount;
            for (int i = 0; i < nodes_to_delete; i++) {
                node<E> *eliminate = poolhead;
                poolhead = poolhead->next;
                delete eliminate;
                poolcount--;
            }
        }
    }

    //==============================================================================
    // --------- insert()

    template <typename E>
    void
    PSLL<E>::insert(E element, int position) {
        if (position > length() || position < 0) throw std::runtime_error("Sorry but that position is outside the current list boundaries");
        else if (position == 0) push_front(element);
        else if (position == length()) push_back(element);
        else {
            node<E> *pre;
            node<E> *cur = head;
            for (int i = 0; i < position; i++) { //iterate though the list until the right position is found
                pre = cur;
                cur = cur->next;
            }
            if (poolcount == 0) { //If there are no free nodes, we need to add a new node before we can push a node to the list
                node<E> *t = new node <E>;
                poolhead = t;
                pooltail = t;
                poolcount++;
            }
            node<E> *to_be_inserted = poolhead;
            poolhead = poolhead->next;
            poolcount--;
            to_be_inserted->datum = element;
            pre->next = to_be_inserted; //link node position-1 to new node	
            to_be_inserted->next = cur; //link new node to position+1 
        }
    }

    //==============================================================================


    template <typename E>
    E * const
    PSLL<E>::contents() {
        size_t const len = length(); //Get the length of the list so that we can now what size array is needed
        E * const contents = new E[len]; //Initialize the array of contents
        node<E> *current = head;
        for (int i = 0; i < len; i++) { //This for loop fills our array with all the datums in order
            contents[i] = current->datum;
            current = current->next;
        }
        return contents;
    }


    //==============================================================================
    // --------- push_back() ------------------------------------------------------------------------------------ IT WORKS

    template <typename E>
    void
    PSLL<E>::push_back(E element) {
        if (poolcount > 0 && head == nullptr) push_front(element);
        else if (poolcount > 0 && head != nullptr) {
            node<E> *ptr = poolhead;
            poolhead = poolhead->next;
            tail ->next = ptr;
            tail = ptr;
            tail->datum = element;
            tail->next = nullptr;
            poolcount--;
            this->psll_rules_check();
        } else if (poolcount == 0) { //If there are no free nodes, we need to add a new node before we can push a node to the list
            node<E> *t = new node <E>;
            poolhead = t;
            pooltail = t;
            poolcount++;
            push_back(element);
        }
    }

    //==============================================================================
    // --------- push_front() ------------------------------------------------------------------------------------ IT WORKS

    template <typename E>
    void
    PSLL<E>::push_front(E element) {
        if (poolcount > 0 && head == nullptr) { //This is the case in which the pool has free nodes and the list is empty

            node<E> *ptr = poolhead; //We point at the pool head
            head = tail = ptr; //We point the had and the tail of the list to our element
            poolhead = poolhead->next;
            head->datum = element; //We make its datum to be element 
            tail->next = nullptr;
            poolcount--;

        } else if (poolcount > 0 && head != nullptr) {
            node<E> *ptr = poolhead; //Temporary pointer created to facilitate the operation
            poolhead = poolhead->next; //New pool head had been assigned
            ptr->datum = element; //Element allocated to free node
            ptr->next = head; //Previously free node being allocated to the front of the list
            head = ptr;
            poolcount--;
            this->psll_rules_check();
        } else if (poolcount == 0) { //If there are no free nodes, we need to add a new node before we can push a node to the list

            node<E> *t = new node <E>;
            poolhead = t;
            pooltail = t;

            poolcount++;
            push_front(element);
        }
    }

    //==============================================================================
    // --------- replace()  --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    PSLL<E>::replace(E element, int position) {
        if (position > length() - 1 || position < 0) throw std::runtime_error("Sorry but that position is outside the current list boundaries");
        node<E> *current = head;
        for (int i = 0; i < position; i++)
            current = current->next;
        E replaced_datum = current->datum;
        current->datum = element;
        return replaced_datum;
    }

    //==============================================================================
    // --------- remove() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    PSLL<E>::remove(int position) {
        if (position > length() - 1 || position < 0) throw std::runtime_error("Sorry but that position is outside the current list boundaries");
        if (position == 0) return pop_front();
        node<E> *previous;
        node<E> *current = head;
        for (int i = 0; i < position; i++) { //Iterate through the list until the position if found
            previous = current;
            current = current->next;
        }
        previous->next = current->next; //Link the node at position-1 to that at position+1
        E deleted_datum = current->datum;
        current->next = poolhead;
        poolhead = current;
        return deleted_datum;
    }

    //==============================================================================
    // --------- pop_back() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    PSLL<E>::pop_back() {
        //First we need to find the last node and the second to last node of our list
        if (is_empty()) throw std::runtime_error("Error from pop_back method: the list is empty");
        if (length() == 1) {
            E deleted_datum = head->datum;
            head->next = poolhead;
            poolhead = head;
            head = nullptr;
            tail = nullptr;
            poolcount++;
            this->psll_rules_check();
            return deleted_datum;
        }
        node<E> *eliminate = head;
        node<E> *previous;
        while (eliminate->next != nullptr) { //Iterate to to the end of the list
            previous = eliminate;
            eliminate = eliminate->next;
        }
        tail = previous; //Turn the node before the old tail into the new tail
        tail->next = nullptr;
        E deleted_datum = eliminate->datum;
        eliminate->next = poolhead;
        poolhead = eliminate;
        poolcount++;
        this->psll_rules_check();
        return deleted_datum;
    }

    //==============================================================================
    // --------- pop_front() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    PSLL<E>::pop_front() {
        if (this->is_empty()) throw std::runtime_error("Error: the list is empty");
        node<E> *eliminate = head;
        E deleted_datum = eliminate->datum;
        head = head->next;
        eliminate->next = poolhead;
        poolhead = eliminate;
        poolcount++;
        this->psll_rules_check();
        return deleted_datum;
    }

    //==============================================================================
    // --------- item_at() --------------------------------------------------------------------------------- IT WORKc

    template <typename E>
    E
    PSLL<E>::item_at(int position) {
        if (position > length() - 1 || position < 0) throw std::runtime_error("Sorry but that position is outside the current list boundaries");
        node<E> *current = head;
        for (int i = 0; i < position; i++) //Iterate though the list until we reach the desired position
            current = current->next;
        return current->datum; //Return the datum at that position    
    }

    //==============================================================================
    // --------- peek_back() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    PSLL<E>::peek_back() {
        if (this->is_empty()) throw std::runtime_error("Error: the list is empty");
        return tail->datum; //Return the tail's datum
    }

    //==============================================================================
    // --------- peek_front() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    PSLL<E>::peek_front() {
        if (this->is_empty()) throw std::runtime_error("Error: the list is empty");
        return head->datum; //Return the head's datum
    }

    //==============================================================================
    // --------- is_empty() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    PSLL<E>::is_empty() {
        if (head == nullptr) return true; //If we don't have a head we don't have anything in the list
        return false;
    }

    //==============================================================================
    // --------- is_full() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    PSLL<E>::is_full(void) {
        return false; //This list can have an infinite amount of nodes and therefore it always returns false 
    }

    //==============================================================================
    // --------- length() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    size_t
    PSLL<E>::length() {
        node<E> *current = head;
        size_t count = 0;
        if (head == nullptr) return count; //If the list is empty the count is zero
        while (current->next != nullptr) { //If the list is not empty we will count the nodes
            count++;
            current = current->next;
        }
        return ++count;
    }

    //==============================================================================
    // --------- clear() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    PSLL<E>::clear() {

        if (this->is_empty()) return;

        while (head != nullptr) //This deletes every element of the list except for the tail
        {
            node<E> *pass_to_pool = head;
            head = head->next;
            pass_to_pool->next = poolhead;
            poolhead = pass_to_pool;
            poolcount++;
            this->psll_rules_check();
        }

        head = nullptr;
        tail = nullptr;

        this->psll_rules_check();
    }

    //==============================================================================
    // --------- contains() --------------------------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    PSLL<E>::contains(E element, bool (*equals_function)(const E&, const E&)) {
        node<E> *current = head;
        if (equals_function(tail->datum, element)) return true; //This checks whether the object we are looking for is in the tail
        while (current->next != nullptr) {//This checks whether the object we are looking for is anywhere else in the list
            if (equals_function(current->datum, element)) return true;
            current = current->next;
        }
        return false;
    }

    //==============================================================================
    // --------- print() ------------------------------------------------------------------------------------ IT WORKS

    template <typename E>
    void
    PSLL<E>::print(std::ostream& o) {
        if (is_empty()) {
            o << "<empty list>" << std::endl;
            return;
        }
        node<E> *t = head;
        int i = 0;
        o << "[";
        while (t->next != nullptr) {
            i++;
            o << t->datum << ",";
            t = t->next;
        }
        o << t->datum << "]";
    }
}
#endif /* PSLL_H */



