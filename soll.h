#ifndef SOLL_H
#define SOLL_H

#include <initializer_list>

// Node structure for singly-linked, ascending, and descending linked lists.
template <typename T>
struct Node {
	T val;         // Value of the node.
    	Node* next;    // Pointer to the next node in the list.
    	Node* prev;    // Pointer to the previous node in the list.
    	Node* asc;     // Pointer to the next node in the ascending list.
    	Node* desc;    // Pointer to the next node in the descending list.
    	Node(const T& v) : val{v}, next{nullptr}, prev{nullptr}, asc{nullptr}, desc{nullptr} {}
};

// SOLL class declaration.
template <typename T>
class SOLL {
public:
    	// Constructor: Initializes an empty SOLL.
    	SOLL();

    	// Destructor: Frees memory and clears the list.
    	~SOLL();

    	// Copy constructor: Creates a deep copy of another SOLL.
    	SOLL(const SOLL&);

    	// Move constructor: Moves ownership of another SOLL.
    	SOLL(SOLL&&);

    	// Constructor from a Node pointer.
    	SOLL(Node<T>*);

    	// Constructor from an initializer list.
    	SOLL(std::initializer_list<T>);

    	// Copy assignment operator: Assigns a deep copy of another SOLL.
    	SOLL& operator=(const SOLL&);

    	// Move assignment operator: Moves ownership of another SOLL.
    	SOLL& operator=(SOLL&&);

    	// Returns a reference to the first element in the list.
    	T& front() const;

    	// Returns a reference to the last element in the list.
    	T& back() const;

    	// Inserts a value at the specified position.
    	void insert(int, const T&);

    	// Appends a value to the end of the list.
    	void push_back(const T&);

    	// Inserts a value at the beginning of the list.
    	void push_front(const T&);

    	// Emplaces a value at the beginning of the list.
    	void emplace_front(const T&);

    	// Removes the last element in the list.
    	void pop_back();

    	// Removes the first element in the list.
    	void pop_front();

    	// Removes all occurrences of a value from the list.
    	void remove(const T&);

    	// Removes an element at the specified position.
    	void erase(int);

    	// Prints the elements in the list.
    	void print();

    	// Prints the elements in ascending order.
    	void printSorted();

    	// Prints the elements in descending order.
    	void printDescendingOrder();

    	// Returns the number of elements in the list.
    	int size() const;

    	// Checks if the list is empty.
    	bool empty() const;

    	// Clears the list.
    	void clear();

    	// Reverses the order of elements in the list.
    	void reverse();

    	// Resizes the list to the specified size.
    	void resize(int);

    	// Swaps the contents of two SOLL instances.
    	void swap(SOLL&);

    	// Splices another SOLL into this list at the specified position.
    	void splice(int, SOLL&);

    	// Merges two sorted SOLL instances into one sorted list.
    	void merge(const SOLL&, const SOLL&);

    	// Sorts the elements in ascending order.
    	void sort();

    	// Returns a reference to the element at the specified position.
    	const T& get(int);

    	// Finds the position of the first occurrence of a value in the list.
    	int find(const T&);

    	// Assigns the specified value to the first 'count' elements in the list.
    	void assign(int, const T&);

    	// Removes duplicate elements from the list.
    	void unique();

    	// Returns a pointer to the head of the list.
    	Node<T>* getHead() const;
private:
	Node<T>* head;
	Node<T>* tail;
	Node<T>* headAsc;
	Node<T>* headDesc;
	void putInOrder(Node<T>*); // Inserts 'node' in ascending order while maintaining the 'headAsc' and 'headDesc' pointers. 
	void removeSortedNode(Node<T>*); // Delete 'node' in ascending order while maintaining the 'headAsc' and 'headDesc' pointers.
	Node<T>* rev(); // Helper function for reverse
	Node<T>* merge(Node<T>*, Node<T>*); // function for merge 2 sorted lists
	Node<T>* midPoint(Node<T>*); // function for find mid point of list
	Node<T>* mergeSort(Node<T>*); // function for merge sort
};

// Comparison operators for SOLL instances.
template <typename T>
bool operator==(const SOLL<T>&, const SOLL<T>&);
template <typename T>
bool operator!=(const SOLL<T>&, const SOLL<T>&);
template <typename T>
bool operator<(const SOLL<T>&, const SOLL<T>&);
template <typename T>
bool operator<=(const SOLL<T>&, const SOLL<T>&);
template <typename T>
bool operator>(const SOLL<T>&, const SOLL<T>&);
template <typename T>
bool operator>=(const SOLL<T>&, const SOLL<T>&);

#include "soll.tpp"

#endif // SOLL_H
