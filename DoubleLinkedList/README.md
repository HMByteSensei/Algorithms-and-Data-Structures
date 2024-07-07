# Double Linked List (DvostrukaLista)

Author: Muhamed Husić

---

This repository contains the implementation of a double linked list (`DvostrukaLista`) in C++. The list supports various operations such as adding elements, removing elements, traversing the list, and finding the maximum element.

## Class `Lista`

An abstract base class defining the interface for a list.

### Public Methods

- `int brojElemenata() const`: Returns the number of elements in the list.
- `Tip &trenutni()`: Returns the current element.
- `Tip trenutni() const`: Returns the current element (const version).
- `bool prethodni()`: Moves to the previous element.
- `bool sljedeci()`: Moves to the next element.
- `void pocetak()`: Moves to the beginning of the list.
- `void kraj()`: Moves to the end of the list.
- `void obrisi()`: Deletes the current element.
- `void dodajIspred(const Tip &el)`: Adds an element before the current element.
- `void dodajIza(const Tip &el)`: Adds an element after the current element.
- `Tip &operator[](int i)`: Accesses the element at index `i`.
- `Tip operator[](int i) const`: Accesses the element at index `i` (const version).

## Class `DvostrukaLista`

A concrete class implementing the double linked list, derived from the abstract `Lista` class.

### Private Members

- `int duzina`: The length of the list.
- `struct Cvor`: A node containing the element and pointers to the next and previous nodes.
- `Cvor *pocetak_liste`: Pointer to the beginning of the list.
- `Cvor *kraj_liste`: Pointer to the end of the list.
- `Cvor *tekuci`: Pointer to the current node.

### Public Methods

- `DvostrukaLista()`: Constructor.
- `~DvostrukaLista()`: Destructor.
- `DvostrukaLista(const DvostrukaLista &l)`: Copy constructor.
- `DvostrukaLista &operator=(const DvostrukaLista &l)`: Copy assignment operator.

### Inherited Methods from `Lista`

- `int brojElemenata() const override`
- `Tip &trenutni() override`
- `Tip trenutni() const override`
- `bool prethodni() override`
- `bool sljedeci() override`
- `void pocetak() override`
- `void kraj() override`
- `void obrisi() override`
- `void dodajIspred(const Tip &el) override`
- `void dodajIza(const Tip &el) override`
- `Tip &operator[](int i) override`
- `Tip operator[](int i) const override`

### Additional Methods

- `template<typename Tip> Tip dajMaksimum(const Lista<Tip>& n)`: Returns the maximum element in the list.

## Test Functions

Several test functions are provided to verify the functionality of the list.

- `template <typename Tip> void generisanjeListe(Lista<Tip> &l)`: Generates a list with elements.
- `template <typename Tip> void prikaziListu(Lista<Tip> &l)`: Displays the list.
- `template <typename TIP> bool testBrojElemenata(Lista<TIP> &l)`: Tests the number of elements in the list.
- `template <typename Tip> bool testIzuzetka(int n, Lista<Tip> &temp)`: Tests if exceptions are thrown.
- `template <typename Tip> void testTrenutni(Lista<Tip> &l, Lista<Tip> &k)`: Tests the `trenutni` method.
- `template <typename Tip> void testPrethodni(Lista<Tip> &l, Lista<Tip> &k)`: Tests the `prethodni` method.
- `template <typename Tip> void testSljedeci(Lista<Tip> &l, Lista<Tip> &k)`: Tests the `sljedeci` method.
- `template <typename Tip> void testPocetak(Lista<Tip> &l, Lista<Tip> &k)`: Tests the `pocetak` method.
- `template <typename Tip> void testKraj(Lista<Tip> &l, Lista<Tip> &k)`: Tests the `kraj` method.
- `template <typename Tip> void testObrisi(Lista<Tip> &l, Lista<Tip> &k)`: Tests the `obrisi` method.
- `template <typename Tip> void testDodajIspred(Lista<Tip> &l)`: Tests the `dodajIspred` method.
- `template <typename Tip> void testDodajIza(Lista<Tip> &l)`: Tests the `dodajIza` method.

## Usage

To use the double linked list, create an instance of the `DvostrukaLista` class and call the desired methods. Here is an example:

