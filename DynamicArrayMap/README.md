# NizMapa

`NizMapa` is a C++ implementation of a simple map (dictionary) data structure using arrays. This class provides basic functionalities to store, access, and manipulate key-value pairs. It is templated to handle various data types for keys (`Kljuc`) and values (`Vrijednost`).

## Table of Contents
- [NizMapa](#nizmapa)
  - [Table of Contents](#table-of-contents)
  - [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Compilation](#compilation)
  - [Usage](#usage)
    - [Creating a Map](#creating-a-map)
    - [Accessing and Modifying Elements](#accessing-and-modifying-elements)
    - [Removing Elements](#removing-elements)
    - [Example Tests](#example-tests)
  - [Functions](#functions)
    - [Constructor](#constructor)
    - [Destructor](#destructor)
    - [Copy Constructor](#copy-constructor)
    - [Assignment Operator](#assignment-operator)
    - [Operator `[]`](#operator-)
    - [brojElemenata](#brojelemenata)
    - [obrisi](#obrisi)
  - [Contributing](#contributing)

## Getting Started

### Prerequisites
To compile and run this code, you need:
- A C++ compiler supporting C++11 or later (e.g., GCC, Clang, MSVC)
- Standard C++ libraries

### Compilation
Compile the code using the following command:

```bash
g++ -std=c++11 -o NizMapa DynamicArrayMap.cpp
```

## Usage

### Creating a Map
```bash
NizMapa<int, double> intToDoubleMap;
NizMapa<std::string, std::string> stringToStringMap;
```

### Accessing and Modifying Elements
Use the operator[] to access and modify elements:
```bash
intToDoubleMap[1] = 1.1;
std::cout << intToDoubleMap[1]; // Outputs: 1.1
stringToStringMap["Key"] = "Value";
std::cout << stringToStringMap["Key"]; // Outputs: Value
```

### Removing Elements
You can remove elements by key or clear the entire map:
```bash
intToDoubleMap.obrisi(1); // Remove the element with key 1
stringToStringMap.obrisi(); // Clear the map
```

## Example Tests
Several test functions are provided to demonstrate the functionality:

- test1(): Basic insertion and access test
- test2(): String key-value pairs with element removal
- test3(): Copy constructor and map clearing
- test4(): Clearing map and assignment
- test5(): Removing elements based on condition

To run the tests, simply execute the compiled program.

## Functions
### Constructor
- NizMapa(): Initializes an empty map with a default capacity.
### Destructor
- ~NizMapa(): Frees dynamically allocated memory.

### Copy Constructor
- NizMapa(const NizMapa<Kljuc, Vrijednost> &n): Copies the elements from another NizMapa.

### Assignment Operator
- NizMapa<Kljuc, Vrijednost> &operator=(const NizMapa &n): Assigns the contents of one map to another.

### Operator []
- Vrijednost &operator[](const Kljuc &k): Accesses or inserts an element.
- Vrijednost operator[](const Kljuc &k) const: Accesses an element in a const context.

### brojElemenata
- int brojElemenata() const: Returns the number of elements in the map.

### obrisi
- void obrisi(): Clears the map.
- void obrisi(const Kljuc &kljuc): Removes the element with the specified key.

## Contributing
Contributions are welcome! Please fork this repository and submit pull requests for any improvements or new features.