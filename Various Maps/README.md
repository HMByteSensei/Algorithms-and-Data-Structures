# Map Data Structures in C++

This project contains implementations of various map data structures in C++, including hash maps, binary search tree maps, and array-based maps.

## Author
- Muhamed Husić

## Files

- **Mapa.h**: Contains the definition of the `Mapa` template class.
- **HashMapa.h**: Contains the definition of the `HashMapa` template class.
- **HashMapa.cpp**: Contains the implementation of the `HashMapa` template class.
- **BinStabloMapa.h**: Contains the definition of the `BinStabloMapa` template class.
- **BinStabloMapa.cpp**: Contains the implementation of the `BinStabloMapa` template class.
- **NizMapa.h**: Contains the definition of the `NizMapa` template class.
- **NizMapa.cpp**: Contains the implementation of the `NizMapa` template class.
- **main.cpp**: Contains the main function.

## Description

This repository contains implementations of various map data structures in C++:
- **HashMapa**: A hash map implementation.
- **BinStabloMapa**: A binary search tree map implementation.
- **NizMapa**: An array-based map implementation.

## Features

### HashMapa

- **Implementation**: Uses hash tables for fast key-value pair operations.
- **Functions**: Includes methods for insertion, deletion, retrieval, and resizing.

### BinStabloMapa

- **Implementation**: Binary search tree structure for sorted key-value pairs.
- **Functions**: Supports insertion, deletion, search, and traversal operations.

### NizMapa

- **Implementation**: Simple array-based map for small to medium-sized collections.
- **Functions**: Provides basic operations like insertion, deletion, and retrieval.

## Usage

### Compilation

To compile the project, use a C++ compiler (e.g., g++):

```bash
g++ -o main main.cpp HashMapa.cpp BinStabloMapa.cpp NizMapa.cpp
```

Run the compiled executable:
```bash
./main
```
