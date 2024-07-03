#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>
#include <vector>

// uslov da svaki vektor sadryi sortirane elemente, i da svaki vektor ima
// elemente koji su veci od svih elemenata predhodnog vektora 
// npr s = {{1,2,10}, {11, 100}}

using namespace std; // za autotestove

template <typename Tip>
class Stek {
private:
    struct Cvor {
        Tip element;
        Cvor *veza; 
    };
    Cvor *pocetak; // ovo je vrh steka
    //Cvor *kraj; // ovo je prvi ubaceni element, znam da moze bez njega ali ovako je implementacija
    // laksa, a memoriski gubitak je zanemariv
    int duzina;
    void daLiJePrazan() const { if(duzina == 0) throw std::range_error("Stek je prazan."); }
public:
    Stek() : duzina(0) { 
        //pocetak = new Cvor(); kraj=pocetak; kraj->veza = nullptr; 
        pocetak = nullptr;
        //pocetak = kraj = nullptr;
    }
    ~Stek() { 
        brisi();
        //delete kraj; 
    }
    Stek(const Stek &s);
    Stek &operator=(Stek &s);

    void brisi();
    void stavi(const Tip& el);
    Tip skini();
    Tip &vrh();
    int brojElemenata() const { return duzina; }
};

template <typename Tip>
Stek<Tip>::Stek(const Stek &s) {
    duzina = s.duzina;
    Cvor *tempIzvor = s.pocetak;
    Cvor *tempDest = new Cvor{tempIzvor->element, nullptr};
    pocetak = tempDest;
    tempIzvor = tempIzvor->veza;
    while(tempIzvor != nullptr) {
        tempDest->veza = new Cvor{tempIzvor->element, nullptr};
        //tempDest->veza = new Cvor();
        tempDest = tempDest->veza;
        tempIzvor = tempIzvor->veza;
    }
}

template <typename Tip>
Stek<Tip> &Stek<Tip>::operator=(Stek<Tip> &s) {
    if(&s == this) return *this;
    brisi();
    duzina = s.duzina;

    if(s.pocetak == nullptr) {
        //pocetak = kraj = nullptr;
        pocetak = nullptr;
        return *this;
    }
    Cvor *tempIzv = s.pocetak;
    Cvor *tempDest = new Cvor{tempIzv->element, nullptr};
    pocetak = tempDest;
    tempIzv = tempIzv->veza;
    while(tempIzv != nullptr) {
        tempDest->veza = new Cvor{tempIzv->element, nullptr}; 
        tempDest = tempDest->veza;
        tempIzv = tempIzv->veza;
    }
    //kraj = tempDest;
    return *this;
}

template <typename Tip>
void Stek<Tip>::brisi() {
    while(pocetak != nullptr) {
    //while(pocetak != kraj) {
        Cvor *temp = pocetak;
        pocetak = pocetak->veza;
        delete temp;
    }
    duzina = 0;
}

template <typename Tip>
void Stek<Tip>::stavi(const Tip& el) {
    Cvor *temp = new Cvor{el, pocetak};
    pocetak = temp;
    duzina++;
}

template <typename Tip>
Tip Stek<Tip>::skini() {
    daLiJePrazan();
    Tip el = pocetak->element;
    Cvor *temp = pocetak;
    pocetak = pocetak->veza;
    delete temp;
    duzina--;
    return el;
}

template <typename Tip>
Tip &Stek<Tip>::vrh() {
    daLiJePrazan();
    return pocetak->element;
}

//------------------------------TRAZENA FUNKCIJA-------------------------------
void pretraga(Stek<std::vector<int> >& s, int trazeni) {
    // za brojanje koliko smo puta izvrsili rekurziju tj koliko je vektora
    // skinuto sa steka
    static int brojac = 0;
    static int brElem = s.brojElemenata();
    if(s.brojElemenata() == 0) {
        std::cout << "Nema elementa";
        return;
    }
    if(!s.vrh().empty()) {
        if(s.vrh().at(0) <= trazeni && s.vrh().at(s.vrh().size() - 1) >= trazeni) {
            int dno = 0;
            int vrh = s.vrh().size()-1;
            while(vrh >= dno) {
                int srednji = (vrh + dno) /2;
                if(s.vrh().at(srednji) == trazeni) {
                    // indeks pocinje od 0 pa zato - 1
                    std::cout << srednji << " " << brElem - brojac - 1; 
                    return;
                } else if(s.vrh().at(srednji) > trazeni) {
                    vrh = srednji - 1;
                } else {
                    dno = srednji + 1;
                }
            }
            std::cout << "Nema elementa";
            return;
        }
    }
    brojac++;
    std::vector<int> temp = s.skini();
    pretraga(s, trazeni);
    s.stavi(temp);
    return;
}
//------------------------------TRAZENA FUNKCIJA-------------------------------


//------------------------------TESTIRANJE-------------------------------
void generiraj(int a, int b, Stek<std::vector<int>> &s) {
    // s = {{a...b},{6,8},{9,10,130},{157,226,3424}}
    std::vector<int> v;
    for(; a<=b; a++) {
        v.push_back(a);
    }
    s.stavi(v);
    s.stavi({6, 8});
    s.stavi({9, 10, 130});
    s.stavi({157, 226, 3424});
    std::cout << "\nStek generiran i ima: " << s.brojElemenata() << " elementa" << std::endl;
}

void prikaziStek(Stek<std::vector<int>> s) {
    int br = s.brojElemenata();
    std::cout << "\n{";
    for(int i=0; i<br; i++) {
        std::cout << "{";
        for(int j = 0; j<s.vrh().size(); j++) {
            std::cout << s.vrh().at(j);
            if(j != s.vrh().size() - 1) {
                std::cout << ",";
            }
        }
        std::cout << "}";
        s.skini();
    }
    std::cout << "}";
}
//------------------------------KRAJ TESTIRANJE---------------------------

/*
// Delete first two lines of code and rename to C++ to test it this way
int main() {
    Stek<std::vector<int>> s;
    generiraj(1, 5, s);
    pretraga(s, 10);
    std::cout << "\n";
    pretraga(s, 11);
    std::cout << "\n";
    pretraga(s, 3425);
    prikaziStek(s);
    return 0;
}
*/