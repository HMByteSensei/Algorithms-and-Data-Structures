#ifndef BINSTABLOMAPA_H
#define BINSTABLOMAPA_H

#include "Mapa.h"
#include <iostream>

template <typename Kljuc, typename Vrijednost>
class BinStabloMapa : public Mapa<Kljuc, Vrijednost> {
private:
    struct Cvor {
        Kljuc kljuc;
        Vrijednost element;
        Cvor *roditelj;
        Cvor *lijevoDijete;
        Cvor *desnoDijete; 
    };
    Cvor *korijen;
    int velicina;
    void postOrderBrisanje(Cvor *trenutni) {
        if(trenutni == nullptr) { return; }
        postOrderBrisanje(trenutni->lijevoDijete);
        postOrderBrisanje(trenutni->desnoDijete);
        delete trenutni;
        velicina--;
    }
    void inOrderispis(Cvor *r) const {
        if(r == nullptr) { return; }
        inOrderispis(r->lijevoDijete);
        std::cout << r->element << " ";
        inOrderispis(r->desnoDijete);
    }
    void preOrderKopiraj(const Cvor *kopija, Cvor *&ovaj) {//, bool daLiJeLijevoDijete) {
        if(kopija != nullptr) {
            //Cvor *novi 
            ovaj = new Cvor{kopija->kljuc, kopija->element, kopija->roditelj, 
                kopija->lijevoDijete, kopija->desnoDijete};
            // if(daLiJeLijevoDijete) {
            //     ovaj->lijevoDijete = novi;
            // } else {
            //     ovaj->desnoDijete = novi;
            // }
            // preOrderKopiraj(kopija, novi, true);
            // preOrderKopiraj(kopija, novi, false);
            preOrderKopiraj(kopija->lijevoDijete, ovaj->lijevoDijete);
            preOrderKopiraj(kopija->desnoDijete, ovaj->desnoDijete);
        }
    }
public:
    BinStabloMapa() : korijen(nullptr), velicina(0) {};
    ~BinStabloMapa() { obrisi(); }
    BinStabloMapa(BinStabloMapa &k);
    BinStabloMapa &operator=(const BinStabloMapa &b);
    Vrijednost &operator[](const Kljuc &k) override;
    Vrijednost operator[](const Kljuc &k) const override;
    int brojElemenata() const override { return velicina; }
    void obrisi() override;
    void obrisi(const Kljuc &kljuc) override;
    void ispisi() const;
};

#endif