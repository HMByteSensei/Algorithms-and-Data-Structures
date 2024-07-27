# Sorting Algorithms and File Operations in C++

This project implements various sorting algorithms and file operations in C++. The code is divided into multiple files for better organization and clarity. Below are the details of the implemented functionalities.

## Files

### 1. `file_operations.h`
This header file contains functions related to file operations such as reading from a file, generating a file with random numbers, and writing sorted data to a file.

- **`void ucitaj(std::string filename, int*& niz, int &vel)`**  
  Reads integers from a file and stores them in an array.

- **`void generisi(std::string filename, int vel)`**  
  Generates a file with random integers.

- **`template <typename Tip> void zapisi(Tip *niz, int vel, std::string filename = "sortirani_nasumicno_generirani.txt")`**  
  Writes the sorted array to a specified file.

### 2. `sorting.h`
This header file includes various sorting algorithms, each implemented as a template function to handle different data types.

- **`template <typename Tip> void bubble_sort(Tip* niz, int vel)`**  
  Implements the bubble sort algorithm.

- **`template <typename Tip> void selection_sort(Tip* niz, int vel)`**  
  Implements the selection sort algorithm.

- **`template <typename Tip> void quick_sort(Tip* niz, int vel)`**  
  Implements the quick sort algorithm using a partitioning function.

- **`template <typename Tip> void merge_sort(Tip* niz, int vel)`**  
  Implements the merge sort algorithm with a helper function for merging.

- **`template <typename Tip> bool daLiJeSortiran(Tip *niz, int vel)`**  
  Checks if an array is sorted.

### 3. `main.cpp`
This file contains the `meni()` function, which provides a user interface for selecting file operations and sorting methods. It also includes the `main()` function, which measures and displays the execution time for the operations.

## Usage

1. **Generate a Random File or Sort an Existing File**  
   Run the program and choose whether to generate a new file with random numbers or to sort an existing file.

2. **Choose Sorting Algorithm**  
   Select a sorting algorithm from the provided options (Bubble Sort, Selection Sort, Quick Sort, Merge Sort).

3. **Output**  
   The program will sort the data and provide an option to save the sorted array to a file.

## Author

- Muhamed Husic

## Note

- The project uses standard C++ libraries and does not require any external dependencies.
- Error handling is implemented for file operations to ensure robustness.
