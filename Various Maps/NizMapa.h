#ifndef NIZMAPA_H
#define NIZMAPA_H

#include "Mapa.h"
#include <utility>

template <typename Kljuc, typename Vrijednost>
class NizMapa : public Mapa<Kljuc, Vrijednost> {
private:
    int kapacitet;
    int brElemenata;
    std::pair<Kljuc, Vrijednost> *niz;
public:
    NizMapa() : kapacitet(1000), brElemenata(0) {
        niz = new std::pair<Kljuc, Vrijednost>[kapacitet]{};
    };
    ~NizMapa() { delete[] niz; };
    NizMapa(const NizMapa<Kljuc, Vrijednost> &n);
    NizMapa<Kljuc, Vrijednost> &operator=(const NizMapa &n);
    Vrijednost &operator[](const Kljuc &k) override;
    Vrijednost operator[](const Kljuc &k) const override;
    int brojElemenata() const override;
    void obrisi() override;
    void obrisi(const Kljuc &kljuc) override; 
};

#endif