# AVL Tree Implementation

Author: Muhamed Husić

---

## Overview

This project contains an implementation of an AVL Tree (self-balancing binary search tree) that maps keys to values. The tree automatically balances itself during insertions and deletions to ensure that the height of the tree remains logarithmic with respect to the number of elements, providing efficient lookup, insertion, and deletion operations.

## Features

- **Balanced Tree:** Ensures the tree remains balanced after every insertion and deletion.
- **Key-Value Mapping:** Maps keys to their corresponding values.
- **Customizable:** Template-based design allows for different data types for keys and values.
- **Pre-order and In-order Traversals:** Functions to print the tree in pre-order and in-order 

## Class Details

### `Mapa`

An abstract base class that defines the interface for the map.

#### Methods:
- `virtual Vrijednost& operator[](const Kljuc& k) = 0;`
- `virtual Vrijednost operator[](const Kljuc& k) const = 0;`
- `virtual int brojElemenata() const = 0;`
- `virtual void obrisi() = 0;`
- `virtual void obrisi(const Kljuc& kljuc) = 0;`

---

### `AVLStabloMapa`

Inherits from `Mapa` and implements the AVL Tree functionality.

#### Methods:
- `Vrijednost& operator[](const Kljuc& k) override;` - Indexing operator `[]`
- `Vrijednost operator[](const Kljuc& k) const override;` - Constant indexing operator `[]`
- `int brojElemenata() const override;` - Number of elements
- `void obrisi() override;` - Clear all elements
- `void obrisi(const Kljuc& kljuc) override;` - Remove element by key
- `void ispisi() const;` - Print elements
- `void preorder();` - Preorder traversal

#### Private Methods:
- `void postOrderBrisanje(Cvor* trenutni);` - Post-order deletion
- `void inOrderIspis(Cvor* r) const;` - In-order print
- `void preOrderKopiraj(const Cvor* kopija, Cvor*& ovaj);` - Pre-order copy
- `void azurirajBalans(Cvor* startRoditelj, bool daLiJeDesnoDijete);` - Update balance
- `void azurirajBalansNakonRotacije(Cvor* startRoditelj, bool daLiJeDesnoDijete);` - Update balance after rotation
- `void rotirajLijevo(Cvor* kriticniCvor);` - Left rotation
- `void rotirajDesno(Cvor* kriticniCvor);` - Right rotation
- `bool desnaGrana(Cvor* trenutni) const;` - Right branch check
- `Kljuc nadjiMax(Cvor* korijen);` - Find maximum key
- `void preorderIspis(Cvor* kopija, const Kljuc& max);` - Preorder print