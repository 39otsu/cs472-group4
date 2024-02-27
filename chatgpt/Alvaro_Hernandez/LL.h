/*
Name: Alvaro Hernandez-Chavez, 5005711017, 1003, Assignment 1
Description: Sorts a linked list of numbers via cocktail sort
Input: filename related to a list of numberes
Output: that list of numbers sorted from least to greatest
*/

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

// Template class for a doubly linked list
template <typename T>
class LL
{
private:
    // Nested structure to represent each node in the linked list
    struct Node
    {
        T data;     // Data held by the node
        Node *prev; // Pointer to the previous node in the list
        Node *next; // Pointer to the next node in the list
    };

    Node *head; // Pointer to the first node in the list
    Node *tail; // Pointer to the last node in the list

public:
    // Iterator class to enable external access to the list's nodes
    class Iterator
    {
    private:
        Node *current; // Pointer to the current node in the iteration

    public:
        // Default constructor initializes current to nullptr
        Iterator() : current(nullptr) {}

        // Constructor initializes current to the given node pointer
        Iterator(Node *ptr) : current(ptr) {}

        // Dereference operator returns the data of the current node
        T operator*() const { return current->data; }

        // Postfix increment operator moves the iterator to the next node
        const Iterator &operator++(int) {
            current = current->next;
            return *this;
        }

        // Postfix decrement operator moves the iterator to the previous node
        const Iterator &operator--(int) {
            current = current->prev;
            return *this;
        }

        // Equality comparison operator
        bool operator==(const Iterator &rhs) const { return current == rhs.current; }

        // Inequality comparison operator
        bool operator!=(const Iterator &rhs) const { return current != rhs.current; }

        // Allow LL to access Iterator's private members
        friend class LL;
    };

    // Default constructor initializes an empty list
    LL() : head(nullptr), tail(nullptr) {}

    // Copy constructor creates a deep copy of the given list
    LL(const LL<T> &copy);

    // Copy assignment operator assigns a deep copy of the given list
    const LL<T> &operator=(const LL<T> &rhs);

    // Destructor deallocates all nodes in the list
    ~LL();

    // Inserts a new node with the given data at the beginning of the list
    void headInsert(const T &item);

    // Inserts a new node with the given data at the end of the list
    void tailInsert(const T &item);

    // Returns an iterator pointing to the first node in the list
    Iterator begin() const;

    // Returns an iterator pointing to the node past the last node in the list
    Iterator end() const;

    // Swaps the positions of the nodes pointed to by the given iterators
    void swapNodes(Iterator &it1, Iterator &it2);
};

// Implementation details for methods, especially those involving complex operations
// like copying and assignment, should follow here. These implementations would include
// thorough comments explaining each step of the process, such as how nodes are copied
// in a deep copy, how the destructor iterates through the list to delete nodes, and how
// swapNodes manages pointers to effectively swap nodes without losing track of the list structure.



//default constructor, sets current to null
template <class T>
LL<T>::Iterator::Iterator()
{
    this->current = NULL;
}
//sets the current to the ptr that was passed
template <class T>
LL<T>::Iterator::Iterator(Node *ptr)
{
    this->current = ptr;
}
//returns the data of the iterator
template <class T>
T LL<T>::Iterator::operator*() const
{
    return this->current->data;
}
//returns the next current
template <class T>
const typename LL<T>::Iterator &LL<T>::Iterator::operator++(int)
{
    current = current->next;
    return *this;
}
//returns the prev current
template <class T>
const typename LL<T>::Iterator &LL<T>::Iterator::operator--(int)
{
    current = current->prev;
    return *this;
}
//checks if the two are equal or not
template <class T>
bool LL<T>::Iterator::operator==(const Iterator &rhs) const
{

    return (this->current == rhs.current);
}
//checks if the two are not equal or yes
template <class T>
bool LL<T>::Iterator::operator!=(const Iterator &rhs) const
{

    return (this->current != rhs.current);
}
//constructor for the linked list, sets the head and tail to NULL
template <class T>
LL<T>::LL()
{
    this->head = NULL;
    this->tail = NULL;
}
//copy constructor for the linked list
template <class T>
LL<T>::LL(const LL<T> &copy)
{
    //makes sure that the copy.head actually has data
    if (copy.head == nullptr)
        head = tail = nullptr;
    //otherwise it will copy all of the content
    else
    {
        head = new Node; //creates a node out of head
        head->data = copy.head->data;
        Node *copyTemp = copy.head->next;
        Node *temp = head;
        //iterates through the copy list and links everything
        while (copyTemp != nullptr)
        {
            temp->next = new Node;
            temp->next->data = copyTemp->data;
            temp->next->next = nullptr;
            temp->next->prev = temp;
            temp = temp->next;
            copyTemp = copyTemp->next;
        }
    }
}

template <class T>
const LL<T> &LL<T>::operator=(const LL<T> &rhs)
{
    if (this == &rhs)
        return *this;
    //checks to make sure that the current list is empty
    //if not empty then make it empty
    if (head != nullptr)
    {
        Node *temp = head;

        while (temp != nullptr)
        {
            Node *deleteNode = temp;
            temp = temp->next;
            delete deleteNode;
        }
        head = tail = nullptr;
    }

    //same comments as before, only real difference is above

    if (rhs.head == nullptr)
        head = tail = nullptr;
    else
    {
        head = new Node;
        head->data = rhs.head->data;
        Node *rhsTemp = rhs.head->next;
        Node *temp = head;

        while (rhsTemp != nullptr)
        {
            temp->next = new Node;
            temp->next->data = rhsTemp->data;
            temp->next->next = nullptr;
            temp->next->prev = temp;
            temp = temp->next;
            rhsTemp = rhsTemp->next;
        }
        tail = temp;
    }

    return *this;
}

//destructor that goes through list and deletes the contents
template <class T>
LL<T>::~LL()
{

    Node *temp = head;

    while (temp != nullptr)
    {
        Node *deleteNode = temp;
        temp = temp->next;
        delete deleteNode;
    }
    head = tail = nullptr;
}
//inserts the item to the beginning of the list
template <class T>
void LL<T>::headInsert(const T &item)
{
    //if head didn't exist already
    if (head == nullptr)
    {
        head = tail = new Node;
        head->data = item;
        head->next = nullptr;
        head->prev = nullptr;
    }
    //if head did exist then simply make it point to the item
    else
    {
        Node *temp = new Node;
        temp->data = item;
        temp->next = head;
        temp->prev = nullptr;
        if (head)
            head->prev = temp;
        head = temp;
    }
}

template <class T>
void LL<T>::tailInsert(const T &item)
{
    //checks if list was empty or not
    if (head == nullptr)
    {
        head = tail = new Node;
        tail->data = item;
        tail->next = nullptr;
        tail->prev = nullptr;
    }
    else
    {
        Node *temp = new Node;
        temp->data = item;
        temp->next = nullptr;
        temp->prev = tail;
        if (tail)
            tail->next = temp;
        tail = temp;
    }
}
//returns an iterator pointed to the head
template <class T>
typename LL<T>::Iterator LL<T>::begin() const
{

    return Iterator(head);
}
//goes through the list until it gets to the last number and returns
template <class T>
typename LL<T>::Iterator LL<T>::end() const
{
    Node *temp = head;
    while (temp->next != nullptr)
        temp = temp->next;
    return Iterator(temp);
}

//Not entirely sure how to credit code yet but this was also heavily inspired
//by the tutorial provided for swapping nodes on geeksforgeeks
//my last one was far more complicated and I ended up having to resort to looking
//up exactly what I was doing wrong
template <class T>
void LL<T>::swapNodes(Iterator &it1, Iterator &it2)
{
    if (head == NULL || head->next == NULL || it1.current == it2.current)
        return;

    //creates nodes to point to the currents
    Node *i1 = it1.current;
    Node *i2 = it2.current;

    // checks for head and tail cases
    if (i1 == head)
        head = i2;
    else if (i2 == head)
        head = i1;
    if (i1 == tail)
        tail = i2;
    else if (i2 == tail)
        tail = i1;
    //switches around the iterators nexts
    Node *temp = i1->next;
    temp = i1->next;
    i1->next = i2->next;
    i2->next = temp;
    //checks to make sure those nexts could be connected back
    if (i1->next != NULL)
        i1->next->prev = i1;
    if (i2->next != NULL)
        i2->next->prev = i2;
    //connects the iterators prevs
    temp = i1->prev;
    i1->prev = i2->prev;
    i2->prev = temp;
    //checks to make sure those prevs could be connected back
    if (i1->prev != NULL)
        i1->prev->next = i1;
    if (i2->prev != NULL)
        i2->prev->next = i2;

    //switches around the currents
    temp = it1.current;
    it1.current = it2.current;
    it2.current = temp;

    return;
}
