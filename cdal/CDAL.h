//Simple Singly-Linked List (CDAL)
//This is the one described in lecture. The idea again is that a linked-list of arrays is used as the backing store. Each array has 50 slots. The chain starts off containing just a single array. When the last array in the chain is filled, and a new item is inserted, a new array is added to the chain.
//Because we don't want the list to waste too much memory, whenever the more than half of the arrays are unused (they would all be at the end of the chain), deallocate half the unused arrays.
// by Iago Patiño López
// with content from https://www.cise.ufl.edu/~dts/ as well as "Algorithms in C++ by Robert Segewick"

#ifndef CDAL_H
#define CDAL_H
#include <stdexcept>
#include <iostream>
#include "List.h"

template <typename E>
struct array_node {
    E datum[50];
    array_node* next;
};

namespace cop3530 {

    template <typename E>
    class CDAL : public List<E> { //We need to create the list class

    public:

        template <typename T>
        class CDAL_Iter {
        public:
            // type aliases required for C++ iterator compatibility
            using value_type = T;
            using reference = T&;
            using pointer = T*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            // type aliases for prettier code
            using self_type = CDAL_Iter;
            using self_reference = CDAL_Iter&;

        private:
            array_node<T> *head;
            int index; //This is the index at which the iterator is
            int array_size;
        public:

            explicit CDAL_Iter(int start = 0, array_node<T> *array = 0, int size = 50) : index(start), head(array), array_size(50) { //This is the explicit constructor for the iterator class. It does not allow implicit conversions or copy-initialization.
            }

            CDAL_Iter(const CDAL_Iter& src) : index(src.index), head(src.head), array_size(src.array_size) { //This is the regular constructor for the iterator class
            }

            reference operator*() const {
                array_node<T> *curr = head;
                int count = 0;
                T *value;
                while (curr) {
                    for (int i = 0; i < array_size; i++)
                        if (count++ == this->index) value = &curr->datum[i];
                    curr = curr->next;
                }
                return *value;
            }

            pointer operator->() const {
                array_node<T> *curr = head;
                int count = 0;
                while (curr) {
                    for (int i = 0; i < array_size; i++)
                        if (count++ == this->index) return &curr->datum[i];
                    curr = curr->next;
                }
                return nullptr;
            }

            self_reference operator=(CDAL_Iter<T> const& src) {
                index = CDAL_Iter(src).index;
                head = CDAL_Iter(src).head;
                array_size = CDAL_Iter(src).array_size;
                return *this;
            }

            self_reference operator++() { //Returns the modified iterator
                index = index + 1;
                return *this;
            } // preincrement

            self_type operator++(int) {
                CDAL_Iter temp(*this);
                index = index + 1;
                return temp;
            } // postincrement

            bool operator==(CDAL_Iter<T> const& rhs) const {
                if (index == rhs.index && head == rhs.head && array_size == rhs.array_size)
                    return true;
                else
                    return false;
            }

            bool operator!=(CDAL_Iter<T> const& rhs) const {
                if (index != rhs.index || head != rhs.head || array_size != rhs.array_size)
                    return true;
                else
                    return false;
            }

        }; // end SDAL_Iter

        using size_t = std::size_t; // you may comment out this line if your compiler complains
        using value_type = E;
        using iterator = CDAL_Iter<E>; //When we use the word iterator, we mean the iterator class
        using const_iterator = CDAL_Iter<E const>;

        //operations
        CDAL(); //This is the constructor method of the singly linked list
        CDAL(const CDAL& other); //copy constructor
        CDAL(CDAL&& other); //move constructor
        ~CDAL(); //This is the destructor method of the singly linked list

        iterator begin() {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return CDAL_Iter<E>(0, head_node, default_size);
        }

        iterator end() {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return CDAL_Iter<E>(tail_index, head_node, default_size);
        }

        const_iterator begin() const {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return CDAL_Iter<E>(0, &head_node, default_size);
        }

        const_iterator end() const {
            if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
            return CDAL_Iter<E>(tail_index, &head_node, default_size);
        }
        CDAL & operator=(const CDAL & other);
        CDAL & operator=(CDAL&& other);
        void insert(E element, int); //Adds the specific element to the list at the specified position, shifting the element originally at that and those in subsequent positions one position to the "right"
        void push_back(E element); //Appends the specified element to the list
        void push_front(E element); //Prepends the specified element to the list
        E replace(E element, int); //Replaces the existing element at the specified position with the specified element and returns the original element
        E remove(int); //Removes and returns the element at the specified position, shifting the subsequent elements one position to the "left"
        E pop_back(void); //Removes and returns the element at the list's tail
        E pop_front(void); //Removes and returns the element at the list's node_head
        E item_at(int); //Returns (without removing from the list) the element at the specified position
        E peek_back(void); //Returns the elements at the list's tail
        E peek_front(void); //Returns the elements at the list's node_head
        bool is_empty(void); //Returns true IFF the list contains no elements
        bool is_full(void); //There isn't a is_full method because a CDAL cannot be full
        size_t length(void); //Returns the number of elements in the list as a size_t
        void clear(void); //removes all elements from the list
        bool contains(E element, bool (*equals_function)(const E&, const E&)); //returns true IFF at least one of the elements of the list matches the specified element
        void print(std::ostream& o); //If the list is empty, inserts "<empty list>" into the ostream; otherwise, inserts, enclosed in square brackets, the list's elements, separated by commas, in sequential order

        E * const contents(); //Allocates, initializes, and returns an array containing a copy of the list's elements in sequential order

    private:
        //variables
        array_node<E> *head_node; //This pointer points at the first node, not the first element of the list
        int tail_index; //This is the index of one pass the last element of the list
        size_t const default_size = 50; //This is the default size of each array

        int last_element_column(); //This tells you in which node(array) the tail is, starting at 0
        int last_element_row(); //Within the column(array) in which tail is, this tells you at which index is the tail
        void adjust_size(); //Whenever we have more than one empty array, it deallocates arrays until there is only one empty array
    };

    //==============================================================================
    // ------- constructor

    template <typename E>
    CDAL<E>::CDAL() {
        tail_index = 0; //We shall start at index 0
        head_node = new array_node<E>;
    }

    //==============================================================================
    // ------- copy constructor

    template <typename E>
    CDAL<E>::CDAL(const CDAL& other) {
        tail_index = other.tail_index;

        //Create the necessary nodes
        head_node = new array_node<E>;
        array_node<E> *temp = head_node;
        for (int i = 0; i < (other.tail_index - 1) / other.default_size; i++) {
            temp->next = new array_node<E>;
            temp = temp->next;
        }

        //Copy the data
        array_node<E> *new_temp = head_node;
        array_node<E> *old_temp = other.head_node;
        for (int i = 0; i <= (other.tail_index - 1) / other.default_size; i++) { //for every column
            for (int i = 0; i < default_size; i++) { //for every row
                new_temp->datum[i] = old_temp->datum[i];
            }
            new_temp = new_temp->next;
            old_temp = old_temp->next;
        }
    }

    //==============================================================================
    // ------- copy-assignment operator

    template <typename E>
    CDAL<E> &
    CDAL<E>::operator=(const CDAL & other) {
        tail_index = other.tail_index;

        //Create the necessary nodes
        head_node = new array_node<E>;
        array_node<E> *temp = head_node;
        for (int i = 0; i < (other.tail_index - 1) / other.default_size; i++) {
            temp->next = new array_node<E>;
            temp = temp->next;
        }

        //Copy the data
        array_node<E> *new_temp = head_node;
        array_node<E> *old_temp = other.head_node;
        for (int i = 0; i <= (other.tail_index - 1) / other.default_size; i++) { //for every column
            for (int i = 0; i < default_size; i++) { //for every row
                new_temp->datum[i] = old_temp->datum[i];
            }
            new_temp = new_temp->next;
            old_temp = old_temp->next;
        }
        return *this;
    }
    // ------  move constructor

    template <typename E>
    CDAL<E>::CDAL(CDAL&& other) {
        head_node = other.head_node;
        tail_index = other.tail_index;

        other.tail_index = 0;
        other.head_node = new array_node<E>;
    }

    // ------- move assignment operator

    template <typename E>
    CDAL<E> &
    CDAL<E>::operator=(CDAL&& other) {
        if (this != &other) {
            head_node = other.head_node;
            tail_index = other.tail_index;

            other.tail_index = 0;
            other.head_node = new array_node<E>;
        }
        return *this;
    }

    // ------  destructor

    template <typename E>
    CDAL<E>::~CDAL() {
    }

    //==============================================================================
    // operations


    //==============================================================================
    // --------- adjust_size()

    template <typename E>
    void
    CDAL<E>::adjust_size() {
        //The following six lines count the number of nodes there are
        size_t number_of_existing_nodes = 0;
        array_node<E> *curr = head_node;
        while (curr) {
            curr = curr->next; //Move to the next node
            number_of_existing_nodes++; //Add an existing node
        }

        //The following section deletes the excess nodes
        if (number_of_existing_nodes - tail_index / default_size > 2) { //If more than one array is empty
            array_node<E> *curr2 = head_node;
            array_node<E> *to_delete;
            for (int i = 0; i < number_of_existing_nodes; i++) { //For each existing node
                to_delete = curr2;
                curr2 = curr2->next;
                if (i > ((tail_index / default_size) + 1)) delete to_delete;
            }
        }
    }

    //==============================================================================
    // --------- row  ------------------------------------------------------------------------------ IT WORKS

    template <typename E>
    int
    CDAL<E>::last_element_row() {
        return (tail_index - 1) % default_size; //Returns the row in which the last list element is, starting at 0
    }

    //==============================================================================
    // --------- column()  ------------------------------------------------------------------------- IT WORKS

    template <typename E>
    int
    CDAL<E>::last_element_column() {
        return (tail_index - 1) / default_size; //Returns the node (column) in which the last list element is, starting at 0
    }

    //==============================================================================
    // --------- insert() -------------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CDAL<E>::insert(E element, int position) {
        if (position == 0) { //If we are inserting at the front, just push front
            push_front(element);
            return;
        }
        if (position == length()) { //If we are inserting at tail, just push back
            push_back(element);
            return;
        }

        //If we are trying to insert further than tail or a negative position, throw an error
        if (position > tail_index || position < 0) throw std::runtime_error("Sorry, cannot insert() outiside the boundaries of the list");

        array_node<E> *insertion_array; //This will be a pointer to the insertion column
        int insertion_column = position / default_size; //This is the column at which insertion must occur
        int insertion_row = position % default_size; //This is the row at which insertion must occur
        array_node<E> *curr_array = head_node;
        E temp1;
        E temp2;
        //The following for loop is used to move every element after the insert position one spot (including the insert position itself) so that there can be enough space for the new element
        for (int column = 0; column <= last_element_column(); column++) { //For every column(array) in which there are elements
            if (column == insertion_column) insertion_array = curr_array; //If we are in the column(array) at which we want to insert, tag it as the insertion_array
            if (curr_array->next == nullptr && last_element_row() >= default_size - 2) curr_array->next = new array_node<E>; //If there is no more space, add a column(array)

            if (column >= insertion_column) { //If we are in the column(array) at which we want to insert or further
                if (column == insertion_column && column != last_element_column()) { //If we are in the right column for insertion but not in the tail column
                    for (int row = insertion_row; row < 50; row++) {
                        if (!(row % 2)) {//If the row is an even number
                            temp1 = curr_array->datum[row];
                            curr_array->datum[row] = temp2;
                        } else {//If the row is an odd number
                            temp2 = curr_array->datum[row];
                            curr_array->datum[row] = temp1;
                        }
                    }
                } else if (column == insertion_column && column == last_element_column()) { //If we are in the right column for insertion and not in the tail column
                    for (int row = insertion_row; row <= last_element_row() + 1; row++) {

                        if (!(row % 2)) {//If row is even
                            temp1 = curr_array->datum[row];
                            curr_array->datum[row] = temp2;
                        } else { //If current row is odd
                            temp2 = curr_array->datum[row];
                            curr_array->datum[row] = temp1;
                        }
                    }
                } else { //If we have passed the column of insertion
                    for (int row = 0; row < default_size; row++) {
                        if (!(row % 2)) {//If the row is even
                            temp1 = curr_array->datum[row];
                            curr_array->datum[row] = temp2;
                        } else {
                            temp2 = curr_array->datum[row];
                            curr_array->datum[row] = temp1;
                        }
                    }
                }
            }
            curr_array = curr_array->next; //Move to the next column(array)
        }

        tail_index++;
        insertion_array->datum[insertion_row] = element; //This inserts the element at the right position
    }

    //==============================================================================
    // --------- contents() -------------------------------------------------------------------------- IT WORKS

    template <typename E>
    E * const
    CDAL<E>::contents() {
        E *contents = new E[tail_index];
        int index = 0;
        array_node<E> *curr = head_node;
        for (int column = 0; column <= last_element_column(); column++) {
            if (column != last_element_column()) {
                for (int row = 0; row < default_size; row++)
                    contents[index++] = curr->datum[row];
            } else {
                for (int row = 0; row <= last_element_row(); row++)
                    contents[index++] = curr->datum[row];
            }
            curr = curr->next;
        }
        return contents;
    }


    //==============================================================================
    // --------- push_back() --------------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CDAL<E>::push_back(E element) {
        tail_index++;
        array_node<E> *current_column = head_node;
        //The following for-loop navigates to the the column(array) of tail and adds more space if necessary
        for (int column = 0; column <= last_element_column(); column++) {
            if (current_column->next == nullptr && last_element_row() == default_size) current_column->next = new array_node<E>; //If there is no more space, add a column(array)
            if (current_column->next) current_column = current_column->next;
        }

        current_column->datum[last_element_row()] = element; //Flls the new tail with the new element.
    }

    //==============================================================================
    // --------- push_front() ---------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CDAL<E>::push_front(E element) {
        //The following for-loop navigates to the the column(array) of tail and adds more space if necessary for insertion
        array_node<E> *current_column = head_node;
        for (int i = 0; i <= last_element_column(); i++) {
            if (current_column->next == nullptr && last_element_row() > default_size - 2) current_column->next = new array_node<E>; //If there is no more space, add a column(array)
            current_column = current_column->next;
        }
        tail_index++;
        E temp1;
        E temp2;
        array_node<E> *temp_node = head_node;

        for (int i = 0; i <= last_element_column(); i++) { //For every column
            for (int j = 0; j <= default_size - 1; j++) { //For every row
                if (!(j % 2)) {//If the number is even
                    temp1 = temp_node->datum[j];
                    temp_node->datum[j] = temp2;
                } else {
                    temp2 = temp_node->datum[j];
                    temp_node->datum[j] = temp1;
                }
            }
            temp_node = temp_node->next;
        }
        head_node->datum[0] = element; //This sets the first item of the list to whatever element is

    }

    //==============================================================================
    // --------- replace() ------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    CDAL<E>::replace(E element, int position) {
        if (position > tail_index - 1 || position < 0)
            throw std::runtime_error("The position requested is outside the list size");
        int column = position / default_size;
        int row = position % default_size;
        array_node<E> *temp = head_node;
        for (int i = 0; i < column; i++) {
            temp = temp->next;
        }
        E eliminate = temp->datum[row];
        temp->datum[row] = element;
        return eliminate;
    }

    //==============================================================================
    // --------- remove() -------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    CDAL<E>::remove(int position) {
        if (position > tail_index - 1 || position < 0) throw std::runtime_error("Sorry, cannot remove an item outside the list boundaries");
        int removal_column = position / default_size;
        int removal_row = position % default_size;
        E to_delete;
        array_node<E> *curr_coulumn = head_node;

        for (int i = 0; i <= last_element_column(); i++) { //For each column until the tail column
            for (int j = 0; j <= default_size; j++) { // For every row in the column in which we are
                if (i == removal_column && j == removal_row) {
                    to_delete = curr_coulumn->datum[removal_row];
                    if (j == default_size - 1 && curr_coulumn->next) {
                        curr_coulumn->datum[j] = curr_coulumn->next->datum[0];
                    } else {
                        curr_coulumn->datum[j] = curr_coulumn->datum[j + 1];
                    }
                } else if (i == removal_column && j >= removal_row) {
                    if (j == default_size - 1 && curr_coulumn->next) {
                        curr_coulumn->datum[j] = curr_coulumn->next->datum[0];
                    } else {
                        curr_coulumn->datum[j] = curr_coulumn->datum[j + 1];
                    }
                } else if (i > removal_column) {
                    if (j == default_size - 1 && curr_coulumn->next) {
                        curr_coulumn->datum[j] = curr_coulumn->next->datum[0];
                    } else {
                        curr_coulumn->datum[j] = curr_coulumn->datum[j + 1];
                    }
                }
            }
            curr_coulumn = curr_coulumn->next;
        }

        tail_index--;
        this->adjust_size();
        return to_delete;
    }

    //==============================================================================
    // --------- pop_back() ------------------------------------------------------------ IT WORKS

    template <typename E>
    E
    CDAL<E>::pop_back() {
        array_node<E> *curr = head_node;

        for (int i = 0; i < last_element_column(); i++) curr = curr->next; //Traverse to the tail column(array)

        E back_item = curr->datum[last_element_row()];

        tail_index--;

        this->adjust_size();

        return back_item;
    }

    //==============================================================================
    // --------- pop_front() ----------------------------------------------------------- IT WORKS

    template <typename E>
    E
    CDAL<E>::pop_front() {
        E front_object = head_node->datum[0];
        array_node<E> *temp_node = head_node;
        for (int i = 0; i <= last_element_column(); i++) {
            for (int j = 0; j <= default_size; j++) {
                temp_node->datum[j] = temp_node->datum[j + 1];
                if (j == default_size - 1 && temp_node->next) {
                    temp_node->datum[j] = temp_node->next->datum[0];
                }
            }
            temp_node = temp_node->next;
        }
        tail_index--;
        this->adjust_size();
        return front_object;
    }

    //==============================================================================
    // --------- item_at() ------------------------------------------------------------- IT WORKS

    template <typename E>
    E
    CDAL<E>::item_at(int position) {
        if (position > tail_index - 1 || position < 0) throw std::runtime_error("The position requested is outside the list size");
        int column = position / default_size;
        int row = position % default_size;
        array_node<E> *temp = head_node;
        for (int i = 0; i < column; i++) {
            temp = temp->next;
        }

        E indexed = temp->datum[row];
        return indexed;
    }

    //==============================================================================
    // --------- peek_back()------------------------------------------------------------ IT WORKS

    template <typename E>
    E
    CDAL<E>::peek_back() {
        return item_at(tail_index - 1);
    }

    //==============================================================================
    // --------- peek_front() ----------------------------------------------------------- IT WORKS

    template <typename E>
    E
    CDAL<E>::peek_front() {
        if (is_empty()) throw std::runtime_error("Sorry, but the list is empty");
        return head_node->datum[0];
    }

    //==============================================================================
    // --------- is_empty() ------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    CDAL<E>::is_empty() {
        return (tail_index == 0);
    }

    //==============================================================================
    // --------- is_full() -------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    CDAL<E>::is_full(void) {
        return false;
    }

    //==============================================================================
    // --------- length() ---------------------------------------------------------------- IT WORKS

    template <typename E>
    size_t
    CDAL<E>::length() {
        return tail_index;
    }

    //==============================================================================
    // --------- clear() ----------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CDAL<E>::clear() {
        tail_index = 0;
        array_node<E> *temp = head_node;
        array_node<E> *to_delete;
        while (temp) {
            to_delete = temp;
            temp = temp->next;
            delete to_delete;
        }
        head_node = new array_node<E>;
    }

    //==============================================================================
    // --------- contains() -------------------------------------------------------------- IT WORKS

    template <typename E>
    bool
    CDAL<E>::contains(E element, bool (*equals_function)(const E&, const E&)) {
        array_node<E> *temp = head_node;
        for (int i = 0; i <= last_element_column(); i++) {
            for (int j = 0; j <= default_size - 1; j++) {
                if (equals_function(temp->datum[j], element) && !(i == last_element_column() && j > last_element_row())) return true;
            }
            temp = temp->next;
        }
        return false;
    }

    //==============================================================================
    // --------- print() ----------------------------------------------------------------- IT WORKS

    template <typename E>
    void
    CDAL<E>::print(std::ostream& o) {
        if (is_empty()) {
            o << "<empty list>" << std::endl;
            return;
        }
        array_node<E> *curr_column = head_node;
        o << "[";
        for (int i = 0; i <= last_element_column(); i++) { //For every column
            if (i != last_element_column()) { //If we are not in the tail column
                for (int j = 0; j < default_size; j++) //For every row
                    o << curr_column->datum[j] << ",";
            } else { //If we are in the tail column
                for (int j = 0; j <= last_element_row(); j++) { //For every row until the tail row
                    if (j == last_element_row()) {
                        o << curr_column->datum[j];
                        break;
                    }
                    o << curr_column->datum[j] << ",";
                }
            }
            curr_column = curr_column->next;
        }
        o << "]";
    }

}


#endif /* CDAL_H */
