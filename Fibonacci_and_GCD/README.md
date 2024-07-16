# Fibonacci and GCD Implementations

Author: Muhamed Husić

---
This project contains C++ implementations of Fibonacci sequence calculations using both iterative and recursive methods. Additionally, it includes a function to compute the greatest common divisor - GCD (NZD function in code) of two integers.

## Files

- `Fibonacci_and_GCD.cpp`: Contains the implementations of the Fibonacci functions and the GCD (nzd function), along with a main function to test them.

## Functions

### Fibonacci Functions

1. `int fib_petlja(int n)`
   - **Description**: Computes the nth Fibonacci number using an iterative approach.
   - **Parameters**:
     - `int n`: The position in the Fibonacci sequence.
   - **Returns**: The nth Fibonacci number.
   - **Example**: `fib_petlja(5)` returns `5`.

2. `int fib2_0(int n, int pretprosli = 0, int prosli = 1)`
   - **Description**: Computes the nth Fibonacci number using a recursive approach.
   - **Parameters**:
     - `int n`: The position in the Fibonacci sequence.
     - `int pretprosli` (optional): The (n-2)th Fibonacci number (default is 0).
     - `int prosli` (optional): The (n-1)th Fibonacci number (default is 1).
   - **Returns**: The nth Fibonacci number.
   - **Example**: `fib2_0(5)` returns `5`.

### GCD Function

1. `int nzd(int x, int y)`
   - **Description**: Computes the greatest common divisor (GCD) of two integers using the Euclidean algorithm.
   - **Parameters**:
     - `int x`: The first integer.
     - `int y`: The second integer.
   - **Returns**: The GCD of `x` and `y`.
   - **Example**: `nzd(6, 2)` returns `2`.
## Performance Comparison

The program measures and compares the execution time of the two Fibonacci functions. The execution time is printed in microseconds.

- `fib_petlja`: Iterative approach
- `fib2_0`: Recursive approach

## Usage

To compile and run the code, use the following commands:

```sh
g++ -o Fibonacci_and_GCD Fibonacci_and_GCD.cpp
./Fibonacci_and_GCD
```


