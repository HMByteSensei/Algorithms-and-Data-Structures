# Queue (Red) Class Implementation

This project implements a queue (FIFO) data structure in C++ using a singly linked list. The `Red` class provides various methods to manipulate the queue such as adding elements, removing elements, and accessing the front element.

## Class Definition

The `Red` class is a template class that supports generic types. It contains private members for managing the queue nodes and methods for common queue operations.

### Private Members

- `struct Cvor`: A structure representing a node in the queue.
  - `Tip element`: The data element stored in the node.
  - `Cvor *veza`: Pointer to the next node in the queue.
- `Cvor *pocetak`: Pointer to the front of the queue.
- `Cvor *kraj`: Pointer to the rear of the queue.
- `int duzina`: The number of elements in the queue.

### Private Methods

- `void daLiJePrazan() const`: Checks if the queue is empty and throws an exception if it is.

### Public Methods

- `Red()`: Default constructor.
- `~Red()`: Destructor.
- `Red(const Red &s)`: Copy constructor.
- `Red &operator=(Red &s)`: Copy assignment operator.
- `void brisi()`: Clears the queue.
- `void stavi(const Tip& el)`: Adds an element to the rear of the queue.
- `Tip skini()`: Removes and returns the front element of the queue.
- `Tip &celo()`: Returns the front element of the queue without removing it.
- `int brojElemenata() const`: Returns the number of elements in the queue.

## Testing Functions

##### `void testStavi(int a, int b, Red<int> &s)`

Adds a range of integers to the queue.

##### `int testBrojElemenata(Red<int> &s)`

Returns the number of elements in the queue.

##### `void prikaziRed(Red<int> s)`

Displays the number of elements in the queue and removes each element.

##### `void testVrh(Red<int> &s)`

Prints the front element of the queue twice.

##### `void testBrisi(Red<int> &s)`

Clears the queue.

## Main Function

The main function demonstrates the usage of the `Red` class and its methods by running a series of tests.

## Notes

- The destructor ensures that all dynamically allocated memory is properly freed.
- The copy constructor and copy assignment operator ensure that deep copies of the queue are made.
- Exception handling is used to manage operations on an empty queue.

## Conclusion

This implementation provides a robust and efficient queue data structure using a singly linked list in C++. The provided methods cover all essential queue operations and ensure proper memory management.
