#include <iostream>

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename Tip>
class DvostraniRed {
private:
    struct Cvor {
        Tip element;
        Cvor *veza; 
        Cvor *sljedeci;
    };
    Cvor *kraj; // ovo je vrh DvostraniReda
    Cvor *pocetak; // ovo je celo
    int duzina;
    void daLiJePrazan() const { if(duzina == 0) throw std::range_error("DvostraniRed je prazan."); }
public:
    DvostraniRed() : duzina(0) {
        pocetak = nullptr;
        kraj = nullptr;
    }
    ~DvostraniRed() { 
        brisi();
    }
    DvostraniRed(const DvostraniRed &s);
    DvostraniRed &operator=(DvostraniRed &s);

    void brisi();
    void staviNaVrh(const Tip& el);
    Tip skiniSaVrha();
    Tip &vrh();
    void staviNaCelo(const Tip& el);
    Tip skiniSaCela();
    Tip &celo();

    int brojElemenata() const { return duzina; }
};

template <typename Tip>
DvostraniRed<Tip>::DvostraniRed(const DvostraniRed &s) {
    duzina = s.duzina;
    if(s.duzina == 0) {
        pocetak = kraj = nullptr;
        return;
    }
    Cvor *tempIzvor = s.kraj;
    Cvor *tempDest = new Cvor{tempIzvor->element, nullptr, nullptr};
    kraj = tempDest;
    //tempIzvor = tempIzvor->veza;
    while(tempIzvor->veza != nullptr) {
        tempIzvor = tempIzvor->veza;
        tempDest->veza = new Cvor{tempIzvor->element, nullptr, tempDest};
        //tempDest->veza = new Cvor();
        tempDest = tempDest->veza;
    }
    // tempDest->veza = new Cvor{tempIzvor->element, nullptr, tempDest};
    // tempDest = tempDest->veza;
    pocetak = tempDest;
}

template <typename Tip>
DvostraniRed<Tip> &DvostraniRed<Tip>::operator=(DvostraniRed<Tip> &s) {
    if(&s == this) return *this;
    brisi();
    duzina = s.duzina;

    if(s.kraj == nullptr) {
        //kraj = kraj = nullptr;
        pocetak = kraj = nullptr;
        return *this;
    }
    Cvor *tempIzv = s.kraj;
    Cvor *tempDest = new Cvor{tempIzv->element, nullptr, nullptr};
    kraj = tempDest;
    //tempIzv = tempIzv->veza;
    while(tempIzv->veza != nullptr) {
        tempIzv = tempIzv->veza;
        tempDest->veza = new Cvor{tempIzv->element, nullptr, tempDest}; 
        tempDest = tempDest->veza;
    }
    // tempDest->veza = new Cvor{tempIzv->element, nullptr, tempDest}; 
    // tempDest = tempDest->veza;
    pocetak = tempDest;
    return *this;
}

template <typename Tip>
void DvostraniRed<Tip>::brisi() {
    pocetak = nullptr;
    while(duzina > 0) {
        Cvor *temp = kraj;
        kraj = kraj->veza;
        delete temp;
        duzina--;
    }
}

template <typename Tip>
void DvostraniRed<Tip>::staviNaVrh(const Tip& el) {
    Cvor *temp = new Cvor{el, kraj, nullptr};
    if(kraj != nullptr) {
        kraj->sljedeci = temp;
    }
    kraj = temp;
    if(duzina == 0) {
        pocetak = kraj;
    }
    duzina++;
}

template <typename Tip>
Tip DvostraniRed<Tip>::skiniSaVrha() {
    daLiJePrazan();
    Tip el = kraj->element;
    Cvor *temp = kraj;
    kraj = kraj->veza;
    delete temp;
    duzina--;
    if(duzina == 0) {
        pocetak = nullptr;
    }
    return el;
}

template <typename Tip>
Tip &DvostraniRed<Tip>::vrh() {
    daLiJePrazan();
    return kraj->element;
}

template <typename Tip>
void DvostraniRed<Tip>::staviNaCelo(const Tip& el) {
    Cvor *temp = new Cvor{el, nullptr, pocetak};
    if(duzina != 0) {
        pocetak->veza = temp;
        pocetak = pocetak->veza;
    }else { 
        pocetak = kraj = temp;
    }
    duzina++;
}

template <typename Tip>
Tip DvostraniRed<Tip>::skiniSaCela() {
    daLiJePrazan();
    Tip el = pocetak->element;
    Cvor *temp = pocetak;
    if(pocetak == kraj) {
        pocetak = kraj = nullptr;
    } else {
        pocetak = pocetak->sljedeci;
    }
    delete temp;
    duzina--;
    return el;
}

template <typename Tip>
Tip& DvostraniRed<Tip>::celo() {
    daLiJePrazan();
    return pocetak->element;
}

//------------------------------TESTIRANJE-------------------------------
void teststaviNaVrh(int a, int b, DvostraniRed<int> &s) {
    for(; a<=b; a++) {
        s.staviNaVrh(a);
    }
}

int testBrojElemenata(DvostraniRed<int> &s) { 
    return s.brojElemenata(); 
}

void prikaziDvostraniRed(DvostraniRed<int> s) { // test kopirajuceg konst i skiniSaVrha
    int br = s.brojElemenata();
    std::cout << "\nBroj elemenata DvostraniReda je: " << br 
            << "\nA izgleda: \n";
    for(int i=0; i<br; i++) {
        std::cout << s.skiniSaVrha() << " ";
    }
}

void testVrh(DvostraniRed<int> &s) {
    std::cout << "\nVrh DvostraniReda je: " << s.vrh() << ", opet: " << s.vrh();
}

void teststaviNaCelo(int a, int b, DvostraniRed<int> &s) {
    for(; a<=b; a++) {
        s.staviNaCelo(a);
    }
}

void prikaziDvostraniRed2(DvostraniRed<int> s) { // test kopirajuceg konst i skiniSaCela
    std::cout << "\nBroj elemenata DvostraniReda je: " << s.brojElemenata();
    for(int i=0; i<s.brojElemenata(); i++) {
        s.skiniSaCela();
    }
}

void testCelo(DvostraniRed<int> &s) {
    std::cout << "\nVrh DvostraniReda je: " << s.celo() << ", opet: " << s.celo();
}

void testBrisi(DvostraniRed<int> &s) {
    s.brisi();
}
//------------------------------KRAJ TESTIRANJE-------------------------------

int main() {
    DvostraniRed<int> s;

    teststaviNaVrh(1, 5, s);
    std::cout << "\ntestBrojElemenata vraca: " << testBrojElemenata(s);
    prikaziDvostraniRed(s);
    testVrh(s);
    testBrisi(s);
    std::cout << "\ntestBrojElemenata vraca: " << testBrojElemenata(s);
    try{
        s.skiniSaVrha();
    } catch(std::range_error e) {
        std::cout << "\n" << e.what() << "\n";
    }

    DvostraniRed<int> r;

    teststaviNaCelo(1, 5, r);
    std::cout << "\ntestBrojElemenata vraca: " << testBrojElemenata(r);
    prikaziDvostraniRed(r);
    testCelo(r);
    testBrisi(r);
    std::cout << "\ntestBrojElemenata vraca: " << testBrojElemenata(r);
    try{
        r.skiniSaCela();
    } catch(std::range_error e) {
        std::cout << "\n" << e.what() << "\n";
    }
    return 0;
}