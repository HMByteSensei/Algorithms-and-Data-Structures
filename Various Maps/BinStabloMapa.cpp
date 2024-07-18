#ifndef BINSTABLOMAPA_CPP
#define BINSTABLOMAPA_CPP

#include "BinStabloMapa.h"
#include <stdexcept>

template <typename Kljuc, typename Vrijednost>
void BinStabloMapa<Kljuc, Vrijednost>::ispisi() const {
    inOrderispis(korijen);
}

template <typename Kljuc, typename Vrijednost>
BinStabloMapa<Kljuc, Vrijednost>::BinStabloMapa(BinStabloMapa<Kljuc, Vrijednost> &k) {
    // if(this->velicina != 0) {
    //     obrisi();
    // }
    korijen = nullptr;
    preOrderKopiraj(k.korijen, korijen);
    this->velicina = k.brojElemenata();
}

template <typename Kljuc, typename Vrijednost>
BinStabloMapa<Kljuc, Vrijednost> &BinStabloMapa<Kljuc, Vrijednost>::operator=(const BinStabloMapa &k) {
    if(this == &k) {
        return *this;
    }
    obrisi();
    korijen = nullptr;
    preOrderKopiraj(k.korijen, korijen);
    this->velicina = k.velicina;
    return *this;
}

template <typename Kljuc, typename Vrijednost>
Vrijednost &BinStabloMapa<Kljuc, Vrijednost>::operator[](const Kljuc &k) {
    Cvor *trenutni = korijen;
    Cvor *roditelj = nullptr;
    while(trenutni != nullptr) {
        if(trenutni->kljuc == k) {
            return trenutni->element;
        } else if(trenutni->kljuc < k) {
            roditelj = trenutni;
            trenutni = trenutni->desnoDijete;
        } else {
            roditelj = trenutni;
            trenutni = trenutni->lijevoDijete;
        }
    }
    Cvor *temp = new Cvor{k, Vrijednost(), roditelj, nullptr, nullptr};
    if(korijen == nullptr) {
        korijen = temp;
    } else if(roditelj->kljuc < k) {
        roditelj->desnoDijete = temp;
    } else if(roditelj->kljuc > k) {
        roditelj->lijevoDijete = temp;
    }
    //std::cout << "\nU metodi []: " << temp->kljuc;
    velicina++;
    //std::cout << "\tvelicina: " << velicina;
    return temp->element;
}

template <typename Kljuc, typename Vrijednost>
Vrijednost BinStabloMapa<Kljuc, Vrijednost>::operator[](const Kljuc &k) const {
    Cvor *trenutni = korijen;
    while(trenutni != nullptr) {
        if(trenutni->kljuc == k) {
            return trenutni->element;
        } else if(trenutni->kljuc < k) {
            trenutni = trenutni->desnoDijete;
        } else {
            trenutni = trenutni->lijevoDijete;
        }
    }
    return Vrijednost();
}

template <typename Kljuc, typename Vrijednost>
void BinStabloMapa<Kljuc, Vrijednost>::obrisi() {
    postOrderBrisanje(korijen);
    korijen = nullptr;
}

template <typename Kljuc, typename Vrijednost>
void BinStabloMapa<Kljuc, Vrijednost>::obrisi(const Kljuc &kljuc) {
    Cvor *p = korijen;
    Cvor *roditelj = nullptr;
    while(p != nullptr && kljuc != p->kljuc) {
        roditelj = p;
        if(kljuc < p->kljuc) {
            p = p->lijevoDijete;
        } else {
            p = p->desnoDijete;
        }
    }
    if(p == nullptr) {
        return;
    }
    Cvor *m;
    if(p->lijevoDijete == nullptr) {
        m = p->desnoDijete;
    } else {
        if(p->desnoDijete == nullptr) {
            m = p->lijevoDijete;
        } else {
            Cvor *pm = p;
            m = p->lijevoDijete;
            Cvor *tmp = m->desnoDijete;
            while(tmp != nullptr) {
                pm = m;
                m = tmp;
                tmp = m->desnoDijete;
            }
            if(pm != p) {
                pm->desnoDijete = m->lijevoDijete;
                m->lijevoDijete = p->lijevoDijete;
            }
            m->desnoDijete = p->desnoDijete;
        }
    }
    if(roditelj == nullptr) {
        korijen = m;
    } else {
        if(p == roditelj->lijevoDijete) {
            roditelj->lijevoDijete = m;
        } else {
            roditelj->desnoDijete = m;
        }
    }
    delete p;
    velicina--;
}

#endif