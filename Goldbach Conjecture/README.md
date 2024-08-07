# Goldbach's Conjecture Solver

## Description

This program demonstrates a simple implementation of Goldbach's Conjecture. The conjecture suggests that every even integer greater than 2 can be expressed as the sum of two prime numbers. The code if successful, prints the pair; otherwise, it reports an error.

## Code Overview

- **`Goldbach` Function**: This function takes an even integer `n` and finds two prime numbers `p` and `q` such that `p + q = n`. If no such pair is found or if the input is invalid, it throws a `std::logic_error`.

- **`main` Function**: Continuously prompts the user to input an even integer, computes the pair of prime numbers (if possible), and measures the execution time of the `Goldbach` function. The program exits when the user inputs `0`.

## Features

- **Prime Number Calculation**: Uses a basic method to find prime numbers up to `n-2`.
- **Execution Time Measurement**: Outputs the time taken to compute the result in milliseconds.
- **Error Handling**: Includes checks for invalid inputs and reports errors accordingly.

## Notes
- The program uses a simple algorithm to check for prime numbers and might not be the most  efficient for very large numbers.
- Make sure to provide valid input to get meaningful results.
