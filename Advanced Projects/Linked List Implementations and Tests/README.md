# Linked Lists

Author: Muhamed Husić

---

## Description
This project includes implementations and tests for various linked list data structures in C++. It contains:

- `LinkedListImplementation.cpp`: Implementation of a singly linked list and array list
- `ListTemplate.h`: Template header file defining a linked list interface.
- `ArrayList.cpp`: Implementation of an array-based list.
- `SingleLinkedList.cpp`: Implementation of an singly linked list.
- `test.h`: Header file for testing utilities.
- `LinkedListAutotest`: Autotest script for continuous integration.

## Files
- `ASPZadaca1.pdf`: File detailing the project requirements and specifications.

### SingleLinkedList (JednostrukaLista)
A singly linked list implementation where each element (node) contains a value and a pointer to the next node in the sequence. Supports deep copying.

#### Methods:
- `brojElemenata()`: Returns the number of elements in the list.
- `trenutni()`: Returns a reference to the current element's value.
- `trenutni() const`: Returns the current element in the list (const version).
- `prethodni()`: Moves the current position to the previous element.
- `sljedeci()`: Moves the current position to the next element.
- `pocetak()`: Sets the current position to the beginning of the list.
- `kraj()`: Sets the current position to the end of the list.
- `obrisi()`: Deletes the current element from the list.
- `dodajIspred(const Tip &el)`: Inserts a new element before the current position.
- `dodajIza(const Tip &el)`: Inserts a new element after the current position.
- `operator[](int i)`: Returns a reference to the element at index `i`.
- `operator[](int i) const`: Returns a copy of the element at index `i`.

### ArrayList (NizLista)
An array-based list implementation with dynamic resizing for efficient element management. Supports deep copying.

#### Methods:
- `brojElemenata()`: Returns the number of elements in the list.
- `trenutni()`: Returns a reference to the current element's value.
- `trenutni() const`: Returns the current element in the list (const version).
- `prethodni()`: Moves the current position to the previous element.
- `sljedeci()`: Moves the current position to the next element.
- `pocetak()`: Sets the current position to the beginning of the list.
- `kraj()`: Sets the current position to the end of the list.
- `obrisi()`: Deletes the current element from the list.
- `dodajIspred(const Tip &el)`: Inserts a new element before the current position.
- `dodajIza(const Tip &el)`: Inserts a new element after the current position.
- `operator[](int i)`: Returns a reference to the element at index `i`.
- `operator[](int i) const`: Returns a copy of the element at index `i`.

## Usage
To compile and run the tests, use the following commands:

```bash
# Compile the project
g++ -o main ArrayList.cpp LinkedListImplementation.cpp SingleLinkedListTest.cpp

# Run the tests
./main
