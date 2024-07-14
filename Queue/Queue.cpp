#include <iostream>
#include <stdexcept>

using namespace std;

template <typename Tip>
class Red {
private:
    struct Cvor {
        Tip element;
        Cvor *veza; 
    };
    Cvor *pocetak; // ovo je celo Reda
    Cvor *kraj;
    int duzina;
    void daLiJePrazan() const { if(duzina == 0) throw std::range_error("Red je prazan."); }
public:
    Red() : duzina(0), kraj(nullptr), pocetak(nullptr) {}
    ~Red() { 
        // while(pocetak != kraj) {
        //     Cvor *temp = pocetak;
        //     pocetak = pocetak->veza;
        //     delete temp;
        // }
        // delete kraj; 
        brisi();
        delete kraj;
    }
    Red(const Red &s);
    Red &operator=(Red &s);

    void brisi();
    void stavi(const Tip& el);
    Tip skini();
    Tip &celo();
    int brojElemenata() const { return duzina; }
};

template <typename Tip>
Red<Tip>::Red(const Red<Tip> &s) {
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
    kraj = tempDest;
}

template <typename Tip>
Red<Tip> &Red<Tip>::operator=(Red<Tip> &s) {
    if(&s == this) return *this;
    brisi();
    //duzina = s.duzina;

    Cvor *temp = s.pocetak;
    while(temp != nullptr) {
        stavi(temp->element);
        temp = temp->veza;
    }
    duzina = s.duzina;
    kraj = temp;
    // if(s.pocetak == nullptr) {
    //     pocetak = kraj = nullptr;
    //     return *this;
    // }
    // Cvor *tempIzv = s.pocetak;
    // Cvor *tempDest = new Cvor{tempIzv->element, nullptr};
    // pocetak = tempDest;
    // tempIzv = tempIzv->veza;
    // while(tempIzv != nullptr) {
    //     tempDest->veza = new Cvor{tempIzv->element, nullptr}; 
    //     tempDest = tempDest->veza;
    //     tempIzv = tempIzv->veza;
    // }
    //kraj = tempDest;
    return *this;
}

template <typename Tip>
void Red<Tip>::brisi() {
    while(pocetak != nullptr) {
        Cvor *temp = pocetak;
        pocetak = pocetak->veza;
        delete temp;
        //temp = nullptr;
    }
    kraj = nullptr;
    duzina = 0;
}

template <typename Tip>
void Red<Tip>::stavi(const Tip& el) {
    Cvor *temp = new Cvor{el, nullptr};//, pocetak}
    // temp->element = el;
    // temp->veza = nullptr;
    if(duzina != 0) {
        kraj->veza = temp;
        kraj = kraj->veza;
    }else { 
        pocetak = kraj = temp;
    }
    duzina++;
}

/*
Pseudo kod s predavanja
1 if (Q.pocetak == NIL) then
2 ERROR („Red je prazan!“)
3 end_if 
4 x = Q.pocetak.info
5 p = Q.pocetak


6 if (Q.pocetak == Q.kraj) then
7 Q.pocetak = Q.kraj = NIL
8 else
9 Q.pocetak = Q.pocetak.sljedeci
10 end_if 
11 FREENODE (p)
12 return x
*/

template <typename Tip>
Tip Red<Tip>::skini() {
    daLiJePrazan();
    Tip el = pocetak->element;
    Cvor *temp = pocetak;
    if(pocetak == kraj) {
        pocetak = kraj = nullptr;
    } else {
        pocetak = pocetak->veza;
    }
    delete temp;
    duzina--;
    if(pocetak == nullptr) {
        kraj = nullptr;
    }
    return el;
}

template <typename Tip>
Tip &Red<Tip>::celo() {
    daLiJePrazan();
    return pocetak->element;
}

//------------------------------TESTIRANJE-------------------------------
void testStavi(int a, int b, Red<int> &s) {
    for(; a<=b; a++) {
        s.stavi(a);
    }
}

int testBrojElemenata(Red<int> &s) { 
    return s.brojElemenata(); 
}

void prikaziRed(Red<int> s) { // test kopirajuceg konst i skini
    std::cout << "\nBroj elemenata reda je: " << s.brojElemenata();
    for(int i=0; i<s.brojElemenata(); i++) {
        s.skini();
    }
}

void testVrh(Red<int> &s) {
    std::cout << "\nVrh reda je: " << s.celo() << ", opet: " << s.celo();
}

void testBrisi(Red<int> &s) {
    s.brisi();
}
//------------------------------KRAJ TESTIRANJE-------------------------------

int main() {
    Red<int> s;

    testStavi(1, 5, s);
    std::cout << "\ntestBrojElemenata vraca: " << testBrojElemenata(s);
    prikaziRed(s);
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