#ifndef HASHMAPA_H
#define HASHMAPA_H

#include "Mapa.h"
#include <functional>
#include <stdexcept>
#include <utility>

template <typename Kljuc, typename Vrijednost>
class HashMapa : public Mapa<Kljuc, Vrijednost> {
private:
    unsigned int kapacitet;
    int brElemenata;
    unsigned int pocetniKapacitet;
    //unsigned int (*zadanHash)(const Kljuc &, unsigned int)=nullptr; // signalizira da nema hash fije
    std::function<unsigned int(const Kljuc&, unsigned int)> zadanHash=nullptr;
    std::pair<Kljuc, std::pair<Vrijednost, bool>> *niz;
    unsigned int hashFunkcija(const Kljuc &k, unsigned int i) const {
        return (zadanHash(k, pocetniKapacitet) + i) % pocetniKapacitet;
    }

public:
    HashMapa() : kapacitet(1000), brElemenata(0), pocetniKapacitet(kapacitet) {
        niz = new std::pair<Kljuc, std::pair<Vrijednost, bool>>[kapacitet]{};
    };
    ~HashMapa() { delete[] niz; };
    HashMapa(const HashMapa<Kljuc, Vrijednost> &n);
    HashMapa<Kljuc, Vrijednost> &operator=(const HashMapa &n);
    Vrijednost &operator[](const Kljuc &k) override;
    Vrijednost operator[](const Kljuc &k) const override;
    int brojElemenata() const override;
    void obrisi() override;
    void obrisi(const Kljuc &kljuc) override; 
    //template<typename H>
    void definisiHashFunkciju(std::function<unsigned int(const Kljuc&, unsigned int)> zadanHash) {
        this->zadanHash = zadanHash;
    }
};

#endif
