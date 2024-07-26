#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <string>
#include <fstream>
#include <random>
#include <iostream>

void ucitaj(std::string filename, int*& niz, int &vel) {
    std::ifstream ulazni_tok;
    ulazni_tok.open(filename);
    if(!ulazni_tok) {
        throw std::ifstream::failure("Otvaranje fajla nije uspjelo.");
    }
    int temp;
    vel = 0; // pocetna velicina
    while(ulazni_tok >> temp) { vel++; }
    ulazni_tok.clear();
    ulazni_tok.seekg(0, std::ios::beg);

    niz = new int[vel];
    for(int i=0; i<vel; i++) {
        ulazni_tok >> niz[i];
    }
} 

void generisi(std::string filename, int vel) {
    std::ofstream izlazni_tok(filename);
    if(!izlazni_tok) {
        throw std::ofstream::failure("Otvaranje fajla nije uspjelo.");
    }

    // random device za generisanje "seed" za "Mersenne twister engine"
    std::random_device rd{};
    // "Mersenne twister engine" za generiranje pseudo-nasumicnih brojeva
    std::mt19937 gen32{rd()};
    std::uniform_real_distribution<double> dist{0.0, 100.0};

    //std::cout << "\nGeneriran fajl sa sljedecim elementima:\n";
    for(int i=0; i<vel; i++) {
        int x = dist(gen32);
        //std::cout << x << "\n";
        izlazni_tok << x;
        izlazni_tok.put(' ');
    }
}

template <typename Tip>
bool daLiJeSortiran(Tip *niz, int vel) {
    for(int i=0; i<vel-1; i++) {
        if(niz[i+1] < niz[i]) {
            return false;
        }
    }
    return true;
}

template <typename Tip>
void zapisi(Tip *niz, int vel, std::string filename = "sortirani_nasumicno_generirani.txt") {
    std::ofstream izlazni_tok(filename);
    if(!izlazni_tok) {
        throw std::ofstream::failure("Otvaranje fajla nije uspjelo.");
    }
    for(int i=0; i<vel; i++) {
        std::cout << "\t" << niz[i];
        izlazni_tok << niz[i];
        izlazni_tok.put(' ');
    }
}

#endif