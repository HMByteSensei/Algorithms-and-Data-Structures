#ifndef HASHMAPA_CPP
#define HASHMAPA_CPP

#include "HashMapa.h"
#include <stdexcept>

template <typename Kljuc, typename Vrijednost>
Vrijednost &HashMapa<Kljuc, Vrijednost>::operator[](const Kljuc &k) {
    if(!zadanHash) {
        throw "Niste unijeli hash funkciju.";
    } 
    if(brElemenata == kapacitet) {
        std::pair<Kljuc, std::pair<Vrijednost, bool>> *novi = new std::pair<Kljuc, std::pair<Vrijednost, bool>>[kapacitet * 2]{};
        for(int i=0; i<kapacitet; i++) {
            novi[i].first = niz[i].first;
            novi[i].second = niz[i].second;
        }
        delete[] niz;
        niz = novi;
        kapacitet *= 2;
        novi = nullptr;
    }
    unsigned int hashIndex;
    int i=0;
    do {
        hashIndex = hashFunkcija(k, i);
        if(k == niz[hashIndex].first) {
            return niz[hashIndex].second.first;
        }
        if(niz[hashIndex].first == Kljuc{} && niz[hashIndex].second.first == Vrijednost{} && niz[hashIndex].second.second == false) {
            break;
        }
        i++;
    } while(i<=brElemenata);

    //std::cout << "\nFija vraca: " << hashIndex << " za kljuc: " << k; 
    niz[hashIndex].first = k;
    niz[hashIndex].second.first = Vrijednost();
    brElemenata++;
    return niz[hashIndex].second.first;
}

template <typename Kljuc, typename Vrijednost>
Vrijednost HashMapa<Kljuc, Vrijednost>::operator[](const Kljuc &k) const {
    if(!zadanHash) {
        throw std::logic_error("Niste unijeli hash funkciju.");
    }
    unsigned int hashIndex = hashFunkcija(k, 0);
    for(int i=0; i<brElemenata; i++) {
        hashIndex = hashFunkcija(k, i);
        if(k == niz[hashIndex].first) {
            return niz[hashIndex].second.first;
        }
        // (0, 0) signalizira da ovo polje nije nikada ni bilo popunjeno
        if(niz[hashIndex].first == (Kljuc{}) && niz[hashIndex].second.first == (Vrijednost{}) && !niz[hashIndex].second.second) {
            break;
        }
    }
    return Vrijednost{};
}

template <typename Kljuc, typename Vrijednost>
int HashMapa<Kljuc, Vrijednost>::brojElemenata() const {
    return brElemenata;
}

template <typename Kljuc, typename Vrijednost>
void HashMapa<Kljuc, Vrijednost>::obrisi() {
    kapacitet /= 4;
    brElemenata = 0;
    delete[] niz;
    niz = new std::pair<Kljuc, std::pair<Vrijednost, bool>>[kapacitet]{};
}

template <typename Kljuc, typename Vrijednost>
void HashMapa<Kljuc, Vrijednost>::obrisi(const Kljuc &k) {
    unsigned int index = hashFunkcija(k, 0); 
    // ako je br elemenata 0 for se ne izvrsi
    for(int i=0; i<brElemenata; i++) {
        index = hashFunkcija(k, i);
        if(niz[index].first == k) {
            // oznaka da je obrisan element
            niz[index].second.second = true;
            niz[index].first = Kljuc{};
            niz[index].second.first = Vrijednost{};
            brElemenata--;
            //std::cout << "\n\t#Obrisan element: " << k << " index: " << index;
            return;
        } 
        if(niz[index].first == Kljuc{} && niz[index].second.first == (Vrijednost{})
            && niz[index].second.second == false) {
            break;
        }
    }
    throw std::invalid_argument("Trazeni element ne postoji u mapi");
}

template <typename Kljuc, typename Vrijednost>
HashMapa<Kljuc, Vrijednost>::HashMapa(const HashMapa<Kljuc, Vrijednost> &n) {
    kapacitet = n.kapacitet;
    brElemenata = n.brElemenata;
    pocetniKapacitet = n.pocetniKapacitet;
    zadanHash = n.zadanHash;
    niz = new std::pair<Kljuc, std::pair<Vrijednost, bool>>[n.kapacitet]{};
    for(int i=0; i<kapacitet; i++) {
        niz[i] = n.niz[i];
    }
}

template<typename Kljuc, typename Vrijednost>
HashMapa<Kljuc, Vrijednost> &HashMapa<Kljuc, Vrijednost>::operator=(const HashMapa<Kljuc, Vrijednost> &n) {
    if(this == &n) {
        return *this;
    }
    delete[] niz;
    kapacitet = n.kapacitet;
    brElemenata = n.brElemenata;
    pocetniKapacitet = n.pocetniKapacitet;
    niz = new std::pair<Kljuc, std::pair<Vrijednost, bool>>[n.kapacitet]{};
    zadanHash = n.zadanHash;
    for(int i=0; i<kapacitet; i++) {
        niz[i] = n.niz[i];
    }
    return *this;
}

#endif