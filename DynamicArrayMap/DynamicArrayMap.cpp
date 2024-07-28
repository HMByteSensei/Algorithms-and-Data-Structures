#include <iostream>
#include <stdexcept>

using namespace std;

template <typename Kljuc, typename Vrijednost>
class Mapa {
public:
    Mapa() {};
    virtual ~Mapa() {};
    virtual Vrijednost &operator[](const Kljuc &k) = 0;
    virtual Vrijednost operator[](const Kljuc &k) const = 0;
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(const Kljuc &kljuc) = 0;
};

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

void test1() {
    std::cout << "\nTest1:\n";
    NizMapa<int, double> testnaMapa;
    testnaMapa[1] = 1.1;
    testnaMapa[2] = 2.2;
    int brElemenata = testnaMapa.brojElemenata();
    std::cout << "Broj elemenata: " << brElemenata << ", a elementi mape su: ";
    for(int i=0; i<brElemenata; i++) {
        std::cout << testnaMapa[i] << "\t";
    }
    std::cout << "\n";
}

void test2() {
    std::cout << "\nTest2:\n";
    NizMapa<string, string> testnaMapa;
    testnaMapa["Prvi"] = "Jedan";
    testnaMapa["Drugi"] = "Dva";
    testnaMapa["Treci"] = "Tri";
    int brElemenata = testnaMapa.brojElemenata();
    std::cout << "Broj elemenata: " << brElemenata << ", a elementi mape su: ";
    testnaMapa.obrisi("Drugi");
    std::cout << "\nPrvi element: " << testnaMapa["Prvi"] << "\nDrugi element: " 
        << testnaMapa["Drugi"] << "\nTreci element: " << testnaMapa["Treci"];
    std::cout << "\n";
}

void test3() {
    std::cout << "\nTest3:\n";
    NizMapa<int, string> testnaMapa;
    testnaMapa[1] = "Jedan";
    testnaMapa[2] = "Dva";
    testnaMapa[3] = "Tri";
    std::cout << "Broj elemenata testne mape: " << testnaMapa.brojElemenata();
    NizMapa<int, string> kopija(testnaMapa);
    testnaMapa.obrisi();
    std::cout << "Broj elemenata testne mape nakon metode obrisi(): " 
        << testnaMapa.brojElemenata();
    std::cout << "Broj elemenata kopije: " << kopija.brojElemenata();
    std::cout << "\n";
}

// Dva outa obrisi nad istom mapom
void test4() {
    std::cout << "\nTest4:\n";
    NizMapa<int, string> testnaMapa;
    testnaMapa[1] = "Jedan";
    testnaMapa[2] = "Dva";
    testnaMapa[3] = "Tri";
    std::cout << "Broj elemenata testne mape: " << testnaMapa.brojElemenata();
    testnaMapa.obrisi();
    NizMapa<int, string> nova = testnaMapa; 
    std::cout << "Broj elemenata testne mape nakon metode obrisi(): " 
        << nova.brojElemenata();
    nova.obrisi();
    std::cout << "Broj elemenata kopije: " << nova.brojElemenata();
    std::cout << "\n";
}

void test5() {
    std::cout << "\nTest5:\n";
    NizMapa<int, string> testnaMapa;
    testnaMapa[1] = "Jedan";
    testnaMapa[2] = "Dva";
    testnaMapa[3] = "N";
    testnaMapa[4] = "N";
    testnaMapa[5] = "N";
    testnaMapa[6] = "N";
    testnaMapa[7] = "N";

    std::cout << "Broj elemenata: " << testnaMapa.brojElemenata();
    int broj_elemenata = testnaMapa.brojElemenata();
    for(int i=1; i<=broj_elemenata; i++) {
        if(i % 2 == 0) {
            testnaMapa.obrisi(i);    
        }
    } 
    std::cout << "\nBroj elemenata: " << testnaMapa.brojElemenata();
    std::cout << "\n";
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    return 0;
}