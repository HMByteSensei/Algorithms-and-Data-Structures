# Stek (Stack) Implementation in C++

This repository contains an implementation of a stack (`Stek`) that stores elements of any type. The stack supports various operations such as pushing, popping, peeking, and checking the number of elements.

## Class Overview

### Stek

#### Public Methods

- `Stek()` - Constructor that initializes an empty stack.
- `~Stek()` - Destructor that cleans up the stack.
- `Stek(const Stek &s)` - Copy constructor.
- `Stek &operator=(Stek &s)` - Copy assignment operator.
- `void brisi()` - Removes all elements from the stack.
- `void stavi(const Tip& el)` - Pushes an element onto the stack.
- `Tip skini()` - Pops an element from the stack.
- `Tip &vrh()` - Returns the top element of the stack.
- `int brojElemenata() const` - Returns the number of elements in the stack.

### Private Methods

- `void daLiJePrazan() const` - Checks if the stack is empty and throws an exception if it is.

## Method Signatures

- `Stek()` - Konstruktor koji inicijalizuje prazan stek.
- `~Stek()` - Destruktor koji briše stek.
- `Stek(const Stek &s)` - Kopirni konstruktor.
- `Stek &operator=(Stek &s)` - Operator za kopiranje.
- `void brisi()` - Briše sve elemente sa steka.
- `void stavi(const Tip& el)` - Dodaje element na stek.
- `Tip skini()` - Uklanja element sa steka.
- `Tip &vrh()` - Vraća element sa vrha steka.
- `int brojElemenata() const` - Vraća broj elemenata na steku.

## Testing

The following testing functions are provided to validate the stack operations:

- `void testStavi(int a, int b, Stek<int> &s)` - Pushes elements from `a` to `b` onto the stack.
- `int testBrojElemenata(Stek<int> &s)` - Returns the number of elements in the stack.
- `void prikaziStek(Stek<int> s)` - Displays the elements of the stack (copy constructor and pop operation test).
- `void testVrh(Stek<int> &s)` - Displays the top element of the stack.
- `void testBrisi(Stek<int> &s)` - Empties the stack.

## Main Function

The `main` function demonstrates the use of the stack and testing functions: