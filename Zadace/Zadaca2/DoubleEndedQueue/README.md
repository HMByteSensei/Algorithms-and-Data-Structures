# DoubleEndedQueue

Author: Muhamed Husić

---

## Description
This project contains an implementation of a doubly-ended queue (`DoubleEndedQueue`) in C++. A doubly-ended queue is a data structure that allows elements to be added or removed from both ends.

## Implementation Details
The `DoubleEndedQueue` is implemented from scratch without using any pre-existing data structures from the C++ Standard Library. It uses a custom-defined doubly-linked list to store elements. Each node contains an element, a pointer to the next node, and a pointer to the previous node. This allows efficient operations at both ends of the queue.

## Features
- **Template Class**: The `DoubleEndedQueue` class is a template, allowing it to store elements of any type.
- **Double-Ended Operations**:
  - `pushToTop` (`staviNaVrh`): Adds an element to the top of the queue.
  - `popFromTop` (`skiniSaVrha`): Removes and returns the element from the top of the queue.
  - `top` (`vrh`): Returns a reference to the element at the top of the queue.
  - `pushToFront` (`staviNaCelo`): Adds an element to the front of the queue.
  - `popFromFront` (`skiniSaCela`): Removes and returns the element from the front of the queue.
  - `front` (`celo`): Returns a reference to the element at the front of the queue.
- **Copy Constructor and Assignment Operator**: Properly handles deep copying.
- **Clear Method**: Clears all elements from the queue.
- **Exception Handling**: Throws `std::range_error` if operations are attempted on an empty queue.
- **Utility Method**: `numberOfElements` (`brojElemenata`) returns the current number of elements in the queue.

## Testing
Basic testing functions are included in the implementation to demonstrate the functionality of the `DoubleEndedQueue` class.
