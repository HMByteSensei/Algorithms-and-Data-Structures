#ifndef NIZMAPA_CPP
#define NIZMAPA_CPP

#include "NizMapa.h"
#include <stdexcept>

template <typename Kljuc, typename Vrijednost>
Vrijednost &NizMapa<Kljuc, Vrijednost>::operator[](const Kljuc &k) {
    for(int i=0; i<brElemenata; i++) {
        if(k == niz[i].first) {
            return niz[i].second;
        }
    }
    if(brElemenata == kapacitet) {
        std::pair<Kljuc, Vrijednost> *novi = new std::pair<Kljuc, Vrijednost>[kapacitet * 2]{};
        for(int i=0; i<brElemenata; i++) {
            novi[i].first = niz[i].first;
            novi[i].second = niz[i].second;
        }
        delete[] niz;
        niz = novi;
        kapacitet *= 2;
        novi = nullptr;
    }
    niz[brElemenata].first = k;
    niz[brElemenata].second = Vrijednost();
    return niz[brElemenata++].second;
}

template <typename Kljuc, typename Vrijednost>
Vrijednost NizMapa<Kljuc, Vrijednost>::operator[](const Kljuc &k) const {
    for(int i=0; i<brElemenata; i++) {
        if(k == niz[i].first) {
            return niz[i].second;
        }
    }
    return Vrijednost{};
}

template <typename Kljuc, typename Vrijednost>
int NizMapa<Kljuc, Vrijednost>::brojElemenata() const {
    return brElemenata;
}

template <typename Kljuc, typename Vrijednost>
void NizMapa<Kljuc, Vrijednost>::obrisi() {
    kapacitet /= 4;
    brElemenata = 0;
    delete[] niz;
    niz = new std::pair<Kljuc, Vrijednost>[kapacitet]{};
}

template <typename Kljuc, typename Vrijednost>
void NizMapa<Kljuc, Vrijednost>::obrisi(const Kljuc &k) {
    for(int i=0; i<brElemenata; i++) {
        if(niz[i].first == k) {
            std::swap(niz[i].first, niz[brElemenata - 1].first);
            std::swap(niz[i].second, niz[brElemenata - 1].second);
            brElemenata--;
            return;
        } 
    }
    throw std::invalid_argument("Trazeni element ne postoji u mapi");
}

template <typename Kljuc, typename Vrijednost>
NizMapa<Kljuc, Vrijednost>::NizMapa(const NizMapa<Kljuc, Vrijednost> &n) {
    kapacitet = n.kapacitet;
    brElemenata = n.brElemenata;
    niz = new std::pair<Kljuc, Vrijednost>[n.kapacitet]{};
    for(int i=0; i<brElemenata; i++) {
        niz[i] = n.niz[i];
    }
}

template<typename Kljuc, typename Vrijednost>
NizMapa<Kljuc, Vrijednost> &NizMapa<Kljuc, Vrijednost>::operator=(const NizMapa<Kljuc, Vrijednost> &n) {
    if(this == &n) {
        return *this;
    }
    delete[] niz;
    kapacitet = n.kapacitet;
    brElemenata = n.brElemenata;
    niz = new std::pair<Kljuc, Vrijednost>[n.kapacitet]{};
    for(int i=0; i<brElemenata; i++) {
        niz[i] = n.niz[i];
    }
    return *this;
}

unsigned int hashFija(int ulaz, unsigned int max) {
    return std::hash<int>{}(ulaz);
}

#endif