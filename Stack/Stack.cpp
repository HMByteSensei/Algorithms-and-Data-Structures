#include <iostream>
#include <stdexcept>

using namespace std;

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

//------------------------------TESTIRANJE-------------------------------
void testStavi(int a, int b, Stek<int> &s) {
    for(; a<=b; a++) {
        s.stavi(a);
    }
}

int testBrojElemenata(Stek<int> &s) { 
    return s.brojElemenata(); 
}

void prikaziStek(Stek<int> s) { // test kopirajuceg konst i skini
    std::cout << "\nBroj elemenata steka je: " << s.brojElemenata();
    for(int i=0; i<s.brojElemenata(); i++) {
        s.skini();
    }
}

void testVrh(Stek<int> &s) {
    std::cout << "\nVrh steka je: " << s.vrh() << ", opet: " << s.vrh();
}

void testBrisi(Stek<int> &s) {
    s.brisi();
}
//------------------------------KRAJ TESTIRANJE-------------------------------

int main() {
    Stek<int> s;

    testStavi(1, 5, s);
    std::cout << "\ntestBrojElemenata vraca: " << testBrojElemenata(s);
    prikaziStek(s);
    testVrh(s);
    testBrisi(s);
    std::cout << "\ntestBrojElemenata vraca: " << testBrojElemenata(s);
    try{
        s.skini();
    } catch(std::range_error e) {
        std::cout << "\n" << e.what() << "\n";
    }
    return 0;
}