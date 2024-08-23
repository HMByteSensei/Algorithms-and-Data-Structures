#ifndef GRANAITERATOR_H 
#define GRANAITERATOR_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <tuple>
#include <queue>
// ne dopusta se da dva cvora imaju vise od jedne grane
template <typename Tip>
class Grana;

template <typename Tip>
class Cvor;

template <typename Tip>
class UsmjereniGraf;

template <typename TipOznake>
class GranaIterator {
    UsmjereniGraf<TipOznake> *ug;
    int pocetna_poz, krajnja_poz;
    //int brojac_inkrementacija;
    GranaIterator() {}
public:
    GranaIterator(UsmjereniGraf<TipOznake> *graf, int poc, int kraj) {
        ug = graf;
        pocetna_poz = poc;
        krajnja_poz = kraj;
        //brojac_inkrementacija = 0;
    }
    Grana<TipOznake> operator*() {return ug->dajGranu(pocetna_poz, krajnja_poz); }
    bool operator==(const GranaIterator &iter) { return &iter == this; }
    bool operator!=(const GranaIterator &iter) { return &iter != this; }
    GranaIterator& operator++() {
        do {
            
            if(krajnja_poz >= ug->dajBrojCvorova()) {
                pocetna_poz++;
                krajnja_poz = 0;
            }
            krajnja_poz++;
        } while(!ug->postojiGrana(pocetna_poz, krajnja_poz) && pocetna_poz >= ug->dajBrojCvorova());
        // if((++brojac_inkrementacija) >= ug->dajBroj);
        return *this;
    }
    GranaIterator operator++(int) {
        GranaIterator<TipOznake> kopija(*this);
        this->operator++();
        return kopija;
    }
};

#endif