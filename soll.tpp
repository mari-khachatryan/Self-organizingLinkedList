#include "soll.h"

#include <iostream>
#include <stdexcept>

template <typename T>
SOLL<T>::SOLL() 
	: head{nullptr}
	, tail{nullptr}
	, headAsc{nullptr}
	, headDesc{nullptr}
{
	// Constructor for the SOLL class. Initializes pointers to nullptr.
}

template <typename T>
void SOLL<T>::clear()
{
	while (!empty())
	{
		pop_front();
	}
	// Clears the list by repeatedly popping elements from the front.
}

template <typename T>
SOLL<T>::~SOLL()
{
	clear();
	// Destructor for the SOLL class. Calls the clear() method to free memory.
} 

template <typename T>
SOLL<T>::SOLL(const SOLL& other)
	: head{nullptr}
	, tail{nullptr}
	, headAsc{nullptr}
	, headDesc{nullptr}
{
	if (!other.empty())
	{
		Node<T>* cur = other.head;
		while (cur) {
			push_back(cur->val);
			cur = cur->next;
		}
	}
	// Copy constructor for the SOLL class. Creates a deep copy of the 'other' list.
}

template <typename T>
SOLL<T>::SOLL(SOLL&& other)
	: head{other.head}
	, tail{other.tail}
	, headAsc{other.headAsc}
	, headDesc{other.headDesc}
{
	other.head = nullptr;
	other.tail = nullptr;
	other.headAsc = nullptr;
	other.headDesc = nullptr;
	// Move constructor for the SOLL class. Moves ownership of pointers from 'other'.
}

template <typename T>
SOLL<T>::SOLL(Node<T>* h)
	: head{h}
{
	// Constructor that takes a Node pointer and sets it as the head.
}

template <typename T>
SOLL<T>::SOLL(std::initializer_list<T> initList)
	: head{nullptr}
	, tail{nullptr}
	, headAsc{nullptr}
	, headDesc{nullptr}
{
	for (const T& val : initList)
	{
		push_back(val);
	}
	// Constructor that initializes the list with elements from an initializer list.
}

template <typename T>
SOLL<T>& SOLL<T>::operator=(const SOLL<T>& other)
{
	if (this == &other) {
		return *this;
	}
	clear();
	Node<T>* current = other.head;
	while (current)
	{
		push_back(current->val);
		current = current->next;
	}
	return *this;
	// Copy assignment operator. Creates a deep copy of the 'other' list.
}

template <typename T>
SOLL<T>& SOLL<T>::operator=(SOLL<T>&& other)
{
	if (this == &other) {
		return *this;
	}
	clear();
	head = other.head;
	tail = other.tail;
	headAsc = other.headAsc;
	headDesc = other.headDesc;
	other.head = nullptr;
	other.tail = nullptr;
	other.headAsc = nullptr;
	other.headDesc = nullptr;
	return *this;
	// Move assignment operator. Moves ownership of pointers from 'other'.
}

template <typename T>
T& SOLL<T>::front() const
{
	if (!head) {
		throw std::runtime_error{"List is empty."};
	}
	return head->val;
	// Returns a reference to the first element in the list.
}

template <typename T>
T& SOLL<T>::back() const
{
	if (!head) {
		throw std::runtime_error{"List is empty."};
	}
	return tail->val;
	// Returns a reference to the last element in the list.
}

template <typename T>
void SOLL<T>::putInOrder(Node<T>* node)
{
	if (!node) return;
    	if (!headAsc) {
        	headAsc = node;
        	headDesc = node;
        	return;
    	}

    	Node<T>* cur = headAsc;
    	while (cur->val < node->val && cur->asc) {
        	cur = cur->asc;
    	}
    	if (cur->val < node->val) {
        	node->asc = cur->asc;
        	cur->asc = node;
        	node->desc = cur;
        	if (!node->asc) {
            		headDesc = node;
        	}
    	} else {
        	node->desc = cur->desc;
        	if (cur->desc) {
            		cur->desc->asc = node;
        	} else {
            		headAsc = node;
        	}
        	node->asc = cur;
        	cur->desc = node;
    	}
    	// Inserts 'node' in ascending order while maintaining the 'headAsc' and 'headDesc' pointers.
}

template <typename T>
void SOLL<T>::push_back(const T& value) 
{
	Node<T>* newNode = new Node<T>(value);
	newNode->prev = tail;
	if (tail)
		tail->next = newNode;
	else 
		head = newNode;
	tail = newNode;
	putInOrder(newNode);
	// Appends a new node with the given value to the end of the list.
}

template <typename T>
void SOLL<T>::push_front(const T& value) 
{
	Node<T>* newNode = new Node<T>(value);
	newNode->next = head;
	if (head) 
	{
		head->prev = newNode;
	}
	else {
		tail = newNode;
	}
    	head = newNode;
    	putInOrder(newNode);
    	// Prepends a new node with the given value to the front of the list.
}

template <typename T>
void SOLL<T>::emplace_front(const T& value)
{
	Node<T>* newNode = new Node<T>(value);
	if (!head)
	{
		head = newNode;
		tail = newNode;
		headAsc = newNode;
		headDesc = newNode;
	}
	else 
	{
		newNode->next = head;
		head->prev = newNode;
		head = newNode;
		Node<T>* nextNode = head->next;
		while (nextNode && nextNode->val <= head->val) {
			nextNode = nextNode->next;
		}
		headDesc = nextNode;
		if (nextNode)
		{
			nextNode->asc = head;
		}
		if (newNode->val < headAsc->val)
		{
			headAsc = newNode;
		}
		putInOrder(newNode);
	}
	// Inserts a new node with the given value at the front while maintaining order.
}

template <typename T>
void SOLL<T>::insert(int pos, const T& value) 
{
	if (pos < 0 || pos > size()) {
		throw std::out_of_range{"Index out of range."};
	}
	if (pos == 0) {
		push_front(value);
	}
	else if (pos == size()) {
		push_back(value);
	}
	Node<T>* node = new Node<T>(value);
    	int count = 0;
    	Node<T>* cur = head;
    	while (count != pos) {
        	++count;
        	cur = cur->next;
    	}
    	cur->prev->next = node;
    	node->prev = cur->prev;
    	cur->prev = node;
    	node->next = cur;
    	putInOrder(node);
    	// Inserts a new node with the given value at the specified position.
}

template <typename T>
void SOLL<T>::print()
{
	Node<T>* curr = head;
	while (curr) {
		std::cout << curr->val << " ";
		curr = curr->next;
	}
	std::cout << "\n";
}

template <typename T>
void SOLL<T>::printSorted()
{
	if (!headAsc) {
        	throw std::out_of_range{"List is empty or headAsc is not initialized."};
    	}
	Node<T>* curr = headAsc;
	while (curr) {
		std::cout << curr->val << " ";
		curr = curr->asc;
	}
	std::cout << "\n";
}

template <typename T>
void SOLL<T>::printDescendingOrder()
{
	if (!headDesc) {
        	throw std::out_of_range{"List is empty or headDesc is not initialized."};
    	}
	Node<T>* curr = headDesc;
	while (curr) {
		std::cout << curr->val << " ";
		curr = curr->desc;
	}
	std::cout << "\n";
}


template <typename T>
int SOLL<T>::size() const
{
	int s = 0;
	Node<T>* curr = head;
	while (curr)
	{
		++s;
		curr = curr->next;
	}
	return s;
}

template <typename T>
bool SOLL<T>::empty() const
{
	return size() == 0;
}

template <typename T>
void SOLL<T>::removeSortedNode(Node<T>* node)
{
	if (!node) {
		return;
	}
	if (node->desc) {
        	node->desc->asc = node->asc;
    	}
    	if (node->asc) {
        	node->asc->desc = node->desc;
    	}
    	// Removes a node from the sorted order (ascending and descending).
}

template <typename T>
void SOLL<T>::pop_back() 
{
    	if (empty()) 
    	{
        	throw std::out_of_range{"List is empty."};
    	} 
    	else 
    	{
        	Node<T>* removed = tail;
        	if (tail == head) 
        	{
            		head = nullptr;
            		tail = nullptr;
        	}
        	else 
        	{
            		tail = tail->prev;
            		tail->next = nullptr;
        	}
        	removeSortedNode(removed);
    	}
    	// Removes the last element from the list.
}

template <typename T>
void SOLL<T>::pop_front() 
{
	if (empty())
	{
		throw std::out_of_range{"List is empty."};
	}
	else 
	{
		Node<T>* removed = head;
		if (head == tail) {
			head = nullptr;
			tail = nullptr;
			headAsc = nullptr;
			headDesc = nullptr;
		}
		else {
			head = head->next;
			head->prev = nullptr;
			headDesc = headDesc->desc;
		}
		removeSortedNode(removed);
	}
	// Removes the first element from the list.
}

template <typename T>
void SOLL<T>::remove(const T& val)
{
	while (head && head->val == val)
	{
		Node<T>* tmp = head;
		head = head->next;
		removeSortedNode(tmp);
		delete tmp;
	}
	Node<T>* cur = head;
	while (cur && cur->next)
	{
		if (cur->next->val == val)
		{
			Node<T>* tmp = cur->next;
			cur->next = tmp->next;
			removeSortedNode(tmp);
			delete tmp;
		}
		else {
			cur = cur->next;
		}
	}
	// Removes all occurrences of a given value from the list.
}

template <typename T>
void SOLL<T>::erase(int pos)
{
	if (pos < 0 || pos >= size())
	{
		throw std::out_of_range{"Index out of range."};
	}
	if (pos == 0)
	{
		pop_front();
	}
	else if (pos == size() - 1)
	{
		pop_back();
	}
	else {
		Node<T>* cur = head;
		for (int i = 0; i < pos - 1; ++i)
		{
			cur = cur->next;
		}
		Node<T>* tmp = cur->next;
		cur->next = tmp->next;
		tmp->next->prev = cur;
		removeSortedNode(tmp);
	}
	// Removes the element at the specified position in the list.
}

template <typename T>
void SOLL<T>::resize(int newSize) {
    	if (newSize < 0) {
        	throw std::out_of_range{"New size must be non-negative."};
    	}
    	int currentSize = size();
    	if (newSize == currentSize) {
        	return; // No change needed.
    	} else if (newSize < currentSize) {
        	// Truncate the list.
        	while (currentSize > newSize) {
            		pop_back();
            		currentSize--;
        	}
    	} else {
        	// Extend the list with default-initialized elements.
        	while (currentSize < newSize) {
            		push_back(T()); // Default-initialized element.
            		currentSize++;
        	}
    	}
    	// Resizes the list to the specified new size.
}

template <typename T>
Node<T>* SOLL<T>::midPoint(Node<T>* list)
{
	Node<T>* slow = list;
	Node<T>* fast = list;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
    	return slow;
    	// Finds the middle point of a list (used in merge sort).
}

template <typename T>
Node<T>* SOLL<T>::merge(Node<T>* list1, Node<T>* list2)
{
    	if (!list1) {
		return list2;
	}
	if (!list2) {
		return list1;
	}
	Node<T>* merged = nullptr;
	if (list1->val <= list2->val) {
		merged = list1;
		merged->next = merge(list1->next, list2);
		if (merged->next) {
			merged->next->prev = merged;
		}
	}
	else {
		merged = list2;
		merged->next = merge(list1, list2->next);
		if (merged->next) {
			merged->next->prev = merged;
		}
	}
	merged->prev = nullptr;
	return merged;
	// Merges two sorted lists into a single sorted list.
}

template <typename T>
Node<T>* SOLL<T>::mergeSort(Node<T>* list)
{
    	if (!list || !list->next) 
	{
		return list;
	}
	Node<T>* mid = midPoint(list);
    	Node<T>* left = list;
    	Node<T>* right = mid;
    	mid->prev->next = nullptr; // Split the list into two separate lists.
    	right->prev = nullptr;
    	left = mergeSort(left);
    	right = mergeSort(right);
    	return merge(left, right);
    	// Performs merge sort on the list.
}

template <typename T>
void SOLL<T>::sort()
{
    	head = mergeSort(head);
    	// Sorts the list in ascending order using merge sort.
}

template <typename T>
void SOLL<T>::merge(const SOLL<T>& list1, const SOLL<T>& list2)
{
	Node<T>* newHead = merge(list1.head, list2.head);
	head = newHead;
	// Merges two lists into the current list.
}

template <typename T>
void SOLL<T>::reverse()
{
	head = rev();
}

template <typename T>
Node<T>* SOLL<T>::rev()
{
	Node<T>* prev = nullptr;
	Node<T>* cur = head;
	Node<T>* nextPtr = nullptr;
	while (cur) {
		nextPtr = cur->next;
		cur->next = prev;
		prev = cur;
		cur = nextPtr;
	}
	return prev;
	// Reverses the order of elements in the list and returns the new head.
}

template <typename T>
void SOLL<T>::swap(SOLL& other)
{
	Node<T>* tmp = head;
	head = other.head;
	other.head = tmp;
	Node<T>* tmpTail = tail;
	tail = other.tail;
	other.tail = tmpTail; 
	Node<T>* tmpAsc = headAsc;
	headAsc = other.headAsc;
	other.headAsc = tmpAsc;
	Node<T>* tmpDesc = headDesc;
	headDesc = other.headDesc;
	other.headDesc = tmpDesc;
	// Swaps the content of two lists.
}

template <typename T>
void SOLL<T>::splice(int pos, SOLL<T>& other) {
    	if (pos < 0 || pos > size()) {
        	throw std::out_of_range{"Position out of range."};
    	}

    	if (other.empty()) {
        	return; // Nothing to splice.
    	}

    	if (pos == 0) {
        	// If pos is 0, prepend the elements from 'other' to the current list.
        	Node<T>* otherTail = other.tail;
        	otherTail->next = head; // Connect the tail of 'other' to the current head.
        	head->prev = otherTail; // Update the previous of the current head.
        	head = other.head; // Update the head to point to the first element of 'other'.
    	} else {
        	Node<T>* cur = head;
        	for (int i = 0; i < pos - 1; ++i) {
            		cur = cur->next;
        	}
        	// Connect the tail of 'other' to the current list.
        	cur->next->prev = other.tail;
        	other.tail->next = cur->next;

        	// Connect the head of 'other' to the current list.
        	cur->next = other.head;
        	other.head->prev = cur;
    	}
    	// Splices elements from 'other' into the current list at the specified position.
}

template <typename T>
void SOLL<T>::assign(int count, const T& val)
{
	for (int i = 0; i < count; ++i)
	{
		push_back(val);
	}
	// Assigns 'count' elements with the given 'val'.
}

template <typename T>
void SOLL<T>::unique()
{
	if (!head)
    	{
        	return; // If the list is empty, nothing to do.
    	}
    	Node<T>* cur = head;
    	while (cur)
    	{
        	Node<T>* prev = cur;
        	Node<T>* nextNode = cur->next;
        	while (nextNode)
        	{
            		if (cur->val == nextNode->val)
            		{
                		Node<T>* duplicate = nextNode;
                		prev->next = nextNode->next;
                		if (nextNode->next) {
                    			nextNode->next->prev = prev; 
                		}
                		removeSortedNode(duplicate);
                		delete duplicate;
            		}
           		else
            		{
                		prev = nextNode;
            		}
            		nextNode = nextNode->next;
        	}
        	cur = cur->next;
    	}
    	// Removes duplicate elements from the list.
}

template <typename T>
const T& SOLL<T>::get(int pos)
{
	Node<T>* cur = head;
	for (int i = 0; i < pos; ++i)
	{
		cur = cur->next;
	}
	return cur->val;
	// Returns the value at the specified position in the list.
}

template <typename T>
int SOLL<T>::find(const T& value)
{
	Node<T>* cur = head;
	int pos = 0;
	while (cur)
	{
		if (cur->val == value)
		{
			return pos;
		}
		cur = cur->next;
		++pos;
	}
	return -1;
	// Finds the first occurrence of 'value' in the list and returns its position.
}

template <typename T>
Node<T>* SOLL<T>::getHead() const
{
	return head;
}

template <typename T>
bool operator==(const SOLL<T>& lhs, const SOLL<T>& rhs)
{
	if (lhs.size() != rhs.size())
	{
		return false;
	}
	Node<T>* cur1 = lhs.getHead();
	Node<T>* cur2 = rhs.getHead();
	while (cur1 && cur2)
	{
		if (cur1->val != cur2->val)
		{
			return false;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return true;
	// Compares two SOLL objects for equality.
}

template <typename T>
bool operator!=(const SOLL<T>& lhs, const SOLL<T>& rhs)
{
	return !(lhs == rhs);
	// Compares two SOLL objects for inequality.
}

template <typename T>
bool operator<(const SOLL<T>& lhs, const SOLL<T>& rhs)
{
	Node<T>* cur1 = lhs.getHead();
	Node<T>* cur2 = rhs.getHead();
	while (cur1 && cur2)
	{
		if (cur1->val < cur2->val)
		{
			return true;
		}
		else if (cur1->val > cur2->val)
		{
			return false;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return (cur1 != nullptr && cur2 != nullptr);
	// Compares two SOLL objects lexicographically for less than.
}

template <typename T>
bool operator<=(const SOLL<T>& lhs, const SOLL<T>& rhs)
{
	Node<T>* cur1 = lhs.getHead();
	Node<T>* cur2 = rhs.getHead();
	while (cur1 && cur2)
	{
		if (cur1->val < cur2->val)
		{
			return true;
		}
		else if (cur1->val > cur2->val)
		{
			return false;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return (cur1 == nullptr);
	// Compares two SOLL objects lexicographically for less than or equal to.
}

template <typename T>
bool operator>(const SOLL<T>& lhs, const SOLL<T>& rhs)
{
	Node<T>* cur1 = lhs.getHead();
	Node<T>* cur2 = rhs.getHead();
	while (cur1 && cur2)
	{
		if (cur1->val > cur2->val)
		{
			return true;
		}
		else if (cur1->val < cur2->val)
		{
			return false;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return (cur1 != nullptr && cur2 != nullptr);
	// Compares two SOLL objects lexicographically for greater than.
}

template <typename T>
bool operator>=(const SOLL<T>& lhs, const SOLL<T>& rhs)
{
	Node<T>* cur1 = lhs.getHead();
	Node<T>* cur2 = rhs.getHead();
	while (cur1 && cur2)
	{
		if (cur1->val > cur2->val)
		{
			return true;
		}
		else if (cur1->val < cur2->val)
		{
			return false;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return (cur1 == nullptr);
	// Compares two SOLL objects lexicographically for greater than or equal to.
}
