#include <iostream>
#include <stdexcept>
#include <functional>
#include <random>

#include "HashMapa.cpp"
#include "NizMapa.cpp"
#include "BinStabloMapa.cpp"

using namespace std;



int main() {
    BinStabloMapa<int, int> stablo;
    NizMapa<int, int> nizMapa;
    HashMapa<int, int> hashMapa;
    hashMapa.definisiHashFunkciju(hashFija);
    // random device za generisanje "seed" za "Mersenne twister engine"
    std::random_device rd{};
    // "Mersenne twister engine" za generiranje pseudo-nasumicnih brojeva
    std::mt19937 gen32{rd()};
    std::uniform_real_distribution<double> dist{0.0, 100.0};

    const int BROJ_ELEMENATA = 1000;

    int  niz[BROJ_ELEMENATA]; // niz u kojem cemo pamtiti random generirane brojeve(kljuceve)

    for(int i=0; i<BROJ_ELEMENATA; i++) {
        niz[i] = dist(gen32);
    }

    clock_t t1 = clock();
    // dodavanje novog elementa u BinStablo
    for(int i=0; i<BROJ_ELEMENATA; i++) {
        stablo[niz[i]] = niz[i];
    }
    clock_t t2 = clock();

    clock_t t3 = clock();
    // dodavanje novog elementa u NizMapa
    for(int i=0; i<BROJ_ELEMENATA; i++) {
        nizMapa[niz[i]] = niz[i];
    }
    clock_t t4 = clock();

    clock_t t5 = clock();
    // dodavanje novog elementa u HashMapu
    for(int i=0; i<BROJ_ELEMENATA; i++) {
        hashMapa[niz[i]] = niz[i];
    }
    clock_t t6 = clock();

    std::cout << "\nVrijeme izvrsavanja potrebno da se unese 100 elemenata u: ";
    std::cout << "\n\t->BinStabloMapa je: " << (t2 - t1) / (CLOCKS_PER_SEC / 1000000);
    std::cout << "\n\t->NizMapa je: " << (t4 - t3) / (CLOCKS_PER_SEC / 1000000);
    std::cout << "\n\t->HashMapa je: " << (t6 - t5) / (CLOCKS_PER_SEC / 1000000);
    t1 = clock();
    // trazenje elementa u BinStablo
    stablo[niz[278]];
    stablo[niz[758]];
    stablo[niz[165]];
    t2 = clock();

    t3 = clock();
    // trazenje elementa u NizMapa
    nizMapa[niz[278]];
    nizMapa[niz[758]];
    nizMapa[niz[165]];
    t4 = clock();

    t5 = clock();
    // trazenje elementa u HashMapa
    hashMapa[niz[278]];
    hashMapa[niz[758]];
    hashMapa[niz[165]];
    t6 = clock();  
    std::cout << "\nVrijeme izvrsavanja potrebno da se pretrazi 100 elemenata u: ";
    std::cout << "\n\t->BinStabloMapa je: " << (t2 - t1) / (CLOCKS_PER_SEC / 1000000);
    std::cout << "\n\t->NizMapa je: " << (t4 - t3) / (CLOCKS_PER_SEC / 1000000);
    std::cout << "\n\t->HashMapa je: " << (t6 - t5) / (CLOCKS_PER_SEC / 1000000);

    t1 = clock();
    // brisanje elementa u BinStablo
    stablo.obrisi(niz[278]);
    stablo.obrisi(niz[758]);
    stablo.obrisi(niz[165]);
    t2 = clock();

    t3 = clock();
    // brisanje elementa u NizMapa
    nizMapa.obrisi(niz[278]);
    nizMapa.obrisi(niz[758]);
    nizMapa.obrisi(niz[165]);
    t4 = clock();

    t5 = clock();
    // brisanje elementa u HashMapa
    hashMapa.obrisi(niz[278]);
    hashMapa.obrisi(niz[758]);
    hashMapa.obrisi(niz[165]);
    t6 = clock();  
    std::cout << "\nVrijeme izvrsavanja potrebno da se obrise elemenat u: ";
    std::cout << "\n\t->BinStabloMapa je: " << (t2 - t1) / (CLOCKS_PER_SEC / 1000000);
    std::cout << "\n\t->NizMapa je: " << (t4 - t3) / (CLOCKS_PER_SEC / 1000000);
    std::cout << "\n\t->HashMapa je: " << (t6 - t5) / (CLOCKS_PER_SEC / 1000000);
    /* 
      vrijeme koje je potrebno da se umetne novi element u NizMapa je manje odnosno
      brze se umecu elementi u NizMapa nego u BinStabloMapa, medutim najbrze se ova akcija odvija u HashMapi. 
      Vrijeme trazenja elementa se odvija jako brzo za sve tri klase.
      Brisanje elementa se odvija brze u HashMapa i NizMapa nego u BinarnoStabloMapa 
    */
    return 0;
}