# Heap Operations and Radix Sort Implementation

Author: Muhamed Husić

---

This C++ program implements various heap operations and the Radix Sort algorithm on vectors of integers. It includes functions to create a heap, insert into a heap, remove the first element from a heap, and perform Radix Sort on a vector.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Implementation Details](#implementation-details)

## Overview

This program provides an implementation of heap operations and Radix Sort for vectors of integers. It includes functionalities to create a heap, insert elements, remove elements, and sort vectors using Radix Sort.

## Features

- **Heap Operations:**
  - Create a heap from a vector
  - Insert an element into the heap
  - Remove the first element from the heap
  - Sort a vector using heap sort
  
- **Radix Sort:**
  - Sort a vector of integers using the Radix Sort algorithm

## Implementation Details

The program includes the following functions:

### Heap Operations
- `nadjiMax(std::vector<int> &a)`: Finds the maximum element in a vector.
- `nadjiBrojCifara(int max)`: Finds the number of digits in the maximum element.
- `radixSort(std::vector<int> &a)`: Sorts a vector using Radix Sort.
- `daLiJeList(std::vector<int> &a, int i, int vel)`: Checks if a node is a leaf in a heap.
- `roditelj(int i)`: Returns the parent index of a given node.
- `desnoDijete(int i)`: Returns the right child index of a given node.
- `lijevoDijete(int i)`: Returns the left child index of a given node.
- `popraviDolje(std::vector<int> &a, int i, int velicina)`: Corrects the heap downwards.
- `stvoriGomilu(std::vector<int> &a)`: Creates a heap from a vector.
- `popraviGore(std::vector<int> &a, int i)`: Corrects the heap upwards.
- `umetniUGomilu(std::vector<int> &a, int umetnuti, int &velicina)`: Inserts an element into the heap.
- `izbaciPrvi(std::vector<int> &a, int &velicina)`: Removes the first element from the heap.
- `gomilaSort(std::vector<int> &a)`: Sorts a vector using heap sort.

### Radix Sort
- `radixSort(std::vector<int> &a)`: Sorts a vector of integers using the Radix Sort algorithm.
