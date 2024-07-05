# HashMapaLan

Author: Muhamed Husić

---

Implementation of a hash map (`HashMapaLan`) using chaining (open addressing) strategy in C++. This class provides basic operations for storing key-value pairs and resizing the internal storage dynamically.

## Table of Contents

- [HashMapaLan](#hashmapalan)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [Methods](#methods)
  - [BFS and DFS](#bfs-and-dfs)
  - [Contributing](#contributing)

## Overview

`HashMapaLan` is a hash map implementation that supports:
- Inserting key-value pairs
- Retrieving values by key
- Deleting elements by key
- Resizing the internal storage when the load factor exceeds a threshold

It also contains BFS and DFS implementations alongside test cases.

## Methods

### Constructor

- `HashMapaLan()`: Initializes the hash map with a default capacity of 1000.

### Destructor

- `~HashMapaLan()`: Releases memory used by the hash map.

### Public Methods

- `operator[]`: Allows access to elements using square brackets for both read and write operations.
- `definisiHashFunkciju`: Defines a custom hash function for the map.
- `brojElemenata()`: Returns the number of elements currently stored.
- `obrisi()`: Clears all elements from the map.
- `obrisi(const Ključ &kljuc)`: Removes the element with the specified key.

## BFS and DFS
### BFS (Breadth-First Search)

Performs Breadth-First Search (BFS) on a directed graph represented by UsmjereniGraf<Tip> starting from a given node cvor.

```cpp
template<typename Tip>
void bfs(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, Cvor<Tip> cvor);
```
`recursiveBFS`
Helper function for BFS that performs the recursive traversal.

```cpp
template<typename Tip>
void recursiveBFS(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, std::queue<Cvor<Tip>> &q);
```

### DFS (Depth-First Search)
Performs Depth-First Search (DFS) on a directed graph represented by UsmjereniGraf<Tip> starting from a given node cvor.

```cpp
template<typename Tip>
void dfs(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, Cvor<Tip> cvor);
```

## Contributing
Contributions to HashMapaLan are welcome!
