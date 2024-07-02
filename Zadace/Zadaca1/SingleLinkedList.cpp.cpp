#include "ListTemplate.h"
#include "test.h"

#include <iostream>

//------------------------------KLASA JEDNOSTRUKA LISTA--------------------
template <typename Tip>
class JednostrukaLista : public Lista<Tip> {
private:
    int duzina;
    struct Cvor {
        Tip element; // predavanje 8b
        Cvor *veza;
    };
    Cvor *cvor_prije;
    Cvor *pocetak_liste = nullptr;
    Cvor *kraj_liste = nullptr;
    Cvor *tekuci;

    void daLiJePrazna() const { if(pocetak_liste == nullptr) throw std::range_error("Lista je prazna!"); }
    void TestIndeksa(int indeks) const { if(indeks < 0 || indeks >= duzina) throw std::range_error("Indeks je van opsega!"); }

public:
    JednostrukaLista() : duzina(0) { cvor_prije = nullptr;pocetak_liste = nullptr; tekuci = nullptr; kraj_liste = nullptr; }
    ~JednostrukaLista();

    JednostrukaLista(const JednostrukaLista &l);
    JednostrukaLista &operator=(const JednostrukaLista &l);

    inline int brojElemenata() const override { return duzina; }

    //-------Ove metode koriste daLiJePrazna-------
    Tip &trenutni() override;
    Tip trenutni() const override;

    bool prethodni() override;
    bool sljedeci() override;
    void pocetak() override;
    void kraj() override;
    void obrisi() override;
    //----------------------------

    void dodajIspred(const Tip &el) override;
    void dodajIza(const Tip &el) override;

    Tip &operator[](int i) override; // za poziv nad nekonstantnim objektima
    Tip operator[](int i) const override;
};
//------------------------------KRAJ KLASE JEDNOSTRUKA LISTA--------------------

template <typename Tip>
JednostrukaLista<Tip>::JednostrukaLista(const JednostrukaLista<Tip> &l) {
    cvor_prije = nullptr;
    duzina = 0;
    pocetak_liste = kraj_liste = tekuci = nullptr;
    Cvor *temp = l.pocetak_liste;
    while(temp != nullptr) {
        dodajIza(temp->element);
        temp = temp->veza;
    }
}

template <typename Tip>
JednostrukaLista<Tip> &JednostrukaLista<Tip>::operator=(const JednostrukaLista &l) {
    if(&l == this) return *this; // Samododjela?
    JednostrukaLista<Tip> temp(l);
    std::swap(duzina, temp.duzina);
    std::swap(tekuci, temp.tekuci);
    std::swap(kraj_liste, temp.kraj_liste);
    std::swap(cvor_prije, temp.cvor_prije);
    std::swap(pocetak_liste, temp.pocetak_liste);
    return *this;
}

template <typename Tip>
JednostrukaLista<Tip>::~JednostrukaLista() {
    //if(pocetak_liste != nullptr) {
        Cvor *temp = pocetak_liste;
        for(Cvor *p; temp != nullptr;) {
            p = temp;
            temp = temp->veza;
            delete p;
            p = nullptr;
        }
        cvor_prije = nullptr;
        pocetak_liste = nullptr;
        kraj_liste = nullptr;
        tekuci = nullptr;
        duzina = 0;
    //}
}

template <typename Tip>
Tip& JednostrukaLista<Tip>::trenutni() {
    daLiJePrazna();
    return tekuci->element;
}

template <typename Tip>
Tip JednostrukaLista<Tip>::trenutni() const {
    daLiJePrazna();
    return tekuci->element;
}

template <typename Tip>
bool JednostrukaLista<Tip>::prethodni() {
    daLiJePrazna();
    if(tekuci == pocetak_liste) return false;
    tekuci = cvor_prije;
    cvor_prije = pocetak_liste;
    if(cvor_prije != tekuci) {
        while(cvor_prije->veza != tekuci) {
            cvor_prije = cvor_prije->veza;
        }
    } else {
        cvor_prije = nullptr;
    }
    return true;
}

template <typename Tip>
bool JednostrukaLista<Tip>::sljedeci()  {
    daLiJePrazna();
    if(tekuci->veza == nullptr) return false;
    cvor_prije = tekuci;
    tekuci = tekuci->veza;
    return true;
}

template <typename Tip>
void JednostrukaLista<Tip>::pocetak() {
    daLiJePrazna();
    tekuci = pocetak_liste;
    cvor_prije = nullptr;
}

template <typename Tip>
void JednostrukaLista<Tip>::kraj() {
    daLiJePrazna();
    tekuci = kraj_liste;
    cvor_prije = pocetak_liste;
    while(cvor_prije->veza != tekuci) {
        cvor_prije = cvor_prije->veza;
    }
}

template <typename Tip>
void JednostrukaLista<Tip>::obrisi() {
    daLiJePrazna();
    //if(duzina - 1 == 0) { cvor_prije = nullptr; }
    if(tekuci == pocetak_liste) {
        // std::cout << "\nTEKUCI->VEZA = " << cvor_prije;
        if(duzina == 1) { /// ako imamo samo 1 element
            delete tekuci;
            tekuci = nullptr;
            cvor_prije = nullptr;
            kraj_liste = nullptr;
            pocetak_liste = nullptr;
            duzina--;
        } else {
            pocetak_liste = pocetak_liste->veza;
            delete tekuci;
            tekuci = pocetak_liste;
            cvor_prije = nullptr;
            duzina--;
        }
    } else {
        Cvor *temp = pocetak_liste;
        while(temp->veza != tekuci) {
            temp = temp->veza;
        }
        cvor_prije = temp;
        temp->veza = tekuci->veza;
        delete tekuci;
        tekuci = temp->veza;
        // OVO
        // cvor_prije = pocetak_liste;
        // while(cvor_prije->veza != tekuci) {
        //     cvor_prije = cvor_prije->veza;
        // }
        if(tekuci == nullptr) {
            //cvor_prije = nullptr; // ovo
            kraj_liste = tekuci = temp;
        }
        duzina--;
    }
}

template <typename Tip>
void JednostrukaLista<Tip>::dodajIza(const Tip &el) {
    if(pocetak_liste == nullptr) {              // tj ako lista nema elemenata
        pocetak_liste = new Cvor{el, nullptr};
        //pocetak_liste->element = el;
        //pocetak_liste->veza = nullptr;
        tekuci = pocetak_liste;
        cvor_prije = nullptr;
        kraj_liste = pocetak_liste;
    } else {
        Cvor *novi = new Cvor{el, tekuci->veza};
        tekuci->veza = novi;
        if(novi->veza == nullptr) {
            kraj_liste = novi;
        }
    }
    duzina++;
}

template <typename Tip>
void JednostrukaLista<Tip>::dodajIspred(const Tip &el) {
    if(pocetak_liste == nullptr) { // nemamo elemenata u listi
        pocetak_liste = new Cvor{el, nullptr};
        tekuci = pocetak_liste;
        cvor_prije = nullptr;
        kraj_liste = tekuci;
    } else {
        if(cvor_prije == nullptr) { // ako ima jedan element u listi, pa cvor_prije je nullptr
            Cvor *novi = new Cvor{el, pocetak_liste};
            cvor_prije = novi;
            kraj_liste = pocetak_liste;
            pocetak_liste = novi;
        } else {
            Cvor *novi = new Cvor{el, cvor_prije->veza};
            cvor_prije->veza = novi;
            cvor_prije = novi;
        }
    }
    duzina++;
}

template <typename Tip>
Tip& JednostrukaLista<Tip>::operator[](int indeks) {
    TestIndeksa(indeks); // provjera da li je indeks uredu
    Cvor *temp = pocetak_liste;
    for(int i=0; i<indeks; i++) {
        temp = temp->veza;
    }
    return temp->element;
    // // predpostavka je da se duzina povecava s dodavanjem broja elemenata
    // // pa ako je TestIndeksa prosao to znaci da Lista nije prazna
    // cvor_prije = pocetak_liste;
    // for(int i=0; i<indeks-1; i++) { // do indeks-1 jer smo vec stavili cvor_prije na pocetak pa je cvor_prije brzi za 1
    //     cvor_prije = cvor_prije->veza;
    // }
    // tekuci = cvor_prije->veza;
    // return tekuci->element;
}

template <typename Tip>
Tip JednostrukaLista<Tip>::operator[](int indeks) const {
    TestIndeksa(indeks);
    Cvor *temp = pocetak_liste;
    for(int i=0; i<indeks; i++) {
        temp = temp->veza;
    }
    return temp->element;
}


int main() {
    NizLista<int> *niz_lista = new NizLista<int>;
    NizLista<int> *prazna_lista_k = new NizLista<int>;
    mainTest(*niz_lista, *prazna_lista_k);

    return 0;
}