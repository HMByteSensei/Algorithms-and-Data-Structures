# Stack Implementation with Generic Elements

Author: Muhamed Husić

---

This C++ program implements a stack (`Stek`) that stores elements of any type (`Tip`). The stack ensures that each element is stored and accessed in Last In, First Out (LIFO) order.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Implementation Details](#implementation-details)
- [Binary Search Function](#binary-search-function)
- [Contributing](#contributing)
- [Usage](#usage)

## Overview

The `Stek` class template provides a generic stack implementation where each stack element (`Cvor`) contains:
- `element`: The stored element of type `Tip`.
- `veza`: Pointer to the next node in the stack.

The class supports basic stack operations such as push (`stavi`), pop (`skini`), peek (`vrh`), checking the number of elements (`brojElemenata`), and clearing the stack (`brisi`).

## Features

- Supports storing elements of any type using templates.
- Implements push, pop, and peek operations.
- Handles exceptions when attempting operations on an empty stack (`std::range_error`).

## Implementation Details

The `Stek` class is implemented using a linked list (`Cvor` structure) where each node (`Cvor`) contains:
- `element`: The stored element of type `Tip`.
- `veza`: Pointer to the next node (`Cvor`) in the stack.

Operations like `stavi`, `skini`, `vrh`, `brojElemenata`, and `brisi` are implemented to manipulate the stack efficiently.

### Binary Search Function (`pretraga`)

The `pretraga` function performs a recursive binary search across the stack elements to find a specified element (`trazeni`). It counts the number of times recursion is executed (`brojac`) and tracks the total number of stack elements (`brElem`). If the element is found, it prints its index and the depth of its vector in the stack (since it was required to do that); otherwise, it indicates that the element isn't found.

# Contributing
Contributions are welcome! Feel free to open issues and pull requests.

## Usage

To use the `Stek` class in your project:

1. Include the `Stek.h` header file in your source code.
2. Instantiate a `Stek<Tip>` object where `Tip` is the type of elements you want to store.
3. Use methods like `stavi`, `skini`, `vrh`, and other provided methods to manipulate the stack.

Example usage:

```cpp
#include "Stek.h"

int main() {
    Stek<int> s; // Example usage with integers
    s.stavi(1);
    s.stavi(2);
    s.stavi(3);

    std::cout << "Top element: " << s.vrh() << std::endl;
    s.skini();
    std::cout << "Top element after pop: " << s.vrh() << std::endl;

    return 0;
}
