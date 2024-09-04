# Graph Algorithms Implementation

## Overview

This project is an implementation of a directed graph (`UsmjereniGraf`) in C++ with functionalities for handling graph vertices (`Cvor`), edges (`Grana`), and graph traversal algorithms such as Breadth-First Search (BFS) and Depth-First Search (DFS). The graph is represented using an adjacency matrix (`MatricaGraf`). The code is modularized into several header files and a main program file.

## Project Structure

The project is organized into the following files:

- **BFS.h**: Contains the implementation of the BFS algorithm.
- **Cvor.h**: Defines the `Cvor` class, representing a vertex in the graph.
- **DFS.h**: Contains the implementation of the DFS algorithm.
- **Grana.h**: Defines the `Grana` class, representing an edge in the graph.
- **GranaIterator.h**: Implements the `GranaIterator` class for iterating over graph edges.
- **MatricaGraf.h**: Implements the `MatricaGraf` class for representing the graph using an adjacency matrix.
- **UsmjereniGraf.h**: Declares the abstract `UsmjereniGraf` class, which is the base for different graph implementations.
- **main.cpp**: The main program file, which demonstrates the use of the graph classes and algorithms.
- **GraphImplementation.cpp**: This file contains the complete implementation.

## Class Descriptions

### `Cvor<Tip>`
Represents a vertex in the graph.

- **`Cvor(UsmjereniGraf<Tip> *graf, int redniBrCvora)`**: Constructor that initializes the vertex with its graph and index.
- **`Tip dajOznaku() const`**: Returns the label of the vertex.
- **`void postaviOznaku(Tip oznaka)`**: Sets the label of the vertex.
- **`int dajRedniBroj() const`**: Returns the index of the vertex.

### `Grana<Tip>`
Represents an edge in the graph.

- **`Grana(UsmjereniGraf<Tip> *graf, int poc, int kraj)`**: Constructor that initializes the edge with its graph and connected vertices.
- **`float dajTezinu() const`**: Returns the weight of the edge.
- **`Tip dajOznaku() const`**: Returns the label of the edge.
- **`void postaviTezinu(float tezina)`**: Sets the weight of the edge.
- **`void postaviOznaku(Tip oznaka)`**: Sets the label of the edge.
- **`Cvor<Tip> dajPolazniCvor() const`**: Returns the starting vertex of the edge.
- **`Cvor<Tip> dajDolazniCvor() const`**: Returns the ending vertex of the edge.

### `GranaIterator<Tip>`
Iterator class for iterating over the edges of the graph.

- **`GranaIterator(UsmjereniGraf<Tip> *graf, int poc, int kraj)`**: Constructor for initializing the iterator.
- **`Grana<Tip> operator*()`**: Returns the edge pointed to by the iterator.
- **`bool operator==(const GranaIterator &iter)`**: Checks if two iterators are equal.
- **`bool operator!=(const GranaIterator &iter)`**: Checks if two iterators are not equal.
- **`GranaIterator& operator++()`**: Pre-increment operator to move the iterator to the next edge.
- **`GranaIterator operator++(int)`**: Post-increment operator to move the iterator to the next edge.

### `MatricaGraf<Tip>`
Represents a graph using an adjacency matrix.

- **`MatricaGraf(int broj)`**: Constructor that initializes the graph with a specified number of vertices.
- **`int dajBrojCvorova() const override`**: Returns the number of vertices in the graph.
- **`void postaviBrojCvorova(int br) override`**: Sets the number of vertices in the graph.
- **`void dodajGranu(int polazni, int dolazni, float tezina) override`**: Adds an edge between two vertices with a specified weight.
- **`void obrisiGranu(int polazni, int dolazni) override`**: Removes the edge between two vertices.
- **`void postaviTezinuGrane(int polazni, int dolazni, float tezina) override`**: Sets the weight of an edge.
- **`float dajTezinuGrane(int polazni, int krajnji) const override`**: Returns the weight of an edge.
- **`bool postojiGrana(int pocetni, int krajnji) const override`**: Checks if an edge exists between two vertices.
- **`void postaviOznakuCvora(int pozicija_cvora, Tip oznaka) override`**: Sets the label of a vertex.
- **`void postaviOznakuGrane(int pocetni, int krajnji, Tip oznaka) override`**: Sets the label of an edge.
- **`Tip dajOznakuCvora(int pozicija_cvora) override`**: Returns the label of a vertex.
- **`Tip dajOznakuGrane(int pocetni, int krajnji) const override`**: Returns the label of an edge.
- **`Grana<Tip>dajGranu(int pocetniCvor, int krajnjiCvor) override`**: Returns an edge between two vertices.
- **`Cvor<Tip> dajCvor(int pozicija) override`**: Returns a vertex at a specified position.

### `UsmjereniGraf<Tip>`
Abstract base class for directed graphs.

- **`UsmjereniGraf(int brojCvorova)`**: Constructor that initializes the graph with a specified number of vertices.
- **`virtual int dajBrojCvorova() const = 0`**: Pure virtual function to get the number of vertices.
- **`virtual ~UsmjereniGraf()`**: Virtual destructor.
- **`virtual void postaviBrojCvorova(int br) = 0`**: Pure virtual function to set the number of vertices.
- **`virtual void dodajGranu(int polazni, int dolazni, float tezina) = 0`**: Pure virtual function to add an edge.
- **`virtual void obrisiGranu(int polazni, int dolazni) = 0`**: Pure virtual function to remove an edge.
- **`virtual void postaviTezinuGrane(int polazni, int dolazni, float tezina) = 0`**: Pure virtual function to set the weight of an edge.
- **`virtual float dajTezinuGrane(int polazni, int krajnji) const = 0`**: Pure virtual function to get the weight of an edge.
- **`virtual bool postojiGrana(int pocetni, int krajnji) const = 0`**: Pure virtual function to check if an edge exists.
- **`virtual void postaviOznakuCvora(int pozicija_cvora, Tip oznaka) = 0`**: Pure virtual function to set the label of a vertex.
- **`virtual void postaviOznakuGrane(int pocetni, int krajnji, Tip oznaka) = 0`**: Pure virtual function to set the label of an edge.
- **`virtual Tip dajOznakuCvora(int pozicija_cvora) = 0`**: Pure virtual function to get the label of a vertex.
- **`virtual Tip dajOznakuGrane(int pocetni, int krajnji) const = 0`**: Pure virtual function to get the label of an edge.
- **`virtual Grana<Tip>dajGranu(int pocetniCvor, int krajnjiCvor) = 0`**: Pure virtual function to get an edge between two vertices.
- **`virtual Cvor<Tip> dajCvor(int pozicija) = 0`**: Pure virtual function to get a vertex at a specified position.

## Graph Traversal Algorithms

### Breadth-First Search (BFS)

- **`void bfs(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, Cvor<Tip> cvor)`**: Performs BFS starting from a given vertex and records the traversal order.
- **`void recursiveBFS(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, std::queue<Cvor<Tip>> &q)`**: Helper function for BFS, processes vertices recursively.

### Depth-First Search (DFS)

- **`void dfs(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, Cvor<Tip> c)`**: Performs DFS starting from a given vertex and records the traversal order.

## How to Run

1. Clone the repository and navigate to the project directory.
2. Compile the project using a C++ compiler, e.g., `g++ -o graph main.cpp`.
3. Run the compiled program: `./graph`.

## Notes

- The graph implementation does not allow multiple edges between the same pair of vertices.
- The traversal functions assume that the vertices and edges are correctly initialized before being passed to the functions.

## Author: HMByteSensei (Muhamed Husić)
