#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <type_traits>
#include <typeinfo>

template <typename Tip> 
class Lista {
public:
  Lista() {}
  virtual ~Lista() {}

  virtual int brojElemenata() const = 0;
  /*
      ako je lista prazna, metode trenutni, prethodni, sljedeci, pocetak, kraj i
     obrisi trebaju baciti izuzetak;
  */
  virtual Tip &trenutni() = 0;
  virtual Tip trenutni() const = 0;

  virtual bool prethodni() = 0;
  virtual bool sljedeci() = 0;
  virtual void pocetak() = 0;
  virtual void kraj() = 0;
  virtual void obrisi() = 0;
  //----------------------------
  virtual void dodajIspred(const Tip &el) = 0;
  virtual void dodajIza(const Tip &el) = 0;

  // predavanje 11a strana 3
  virtual Tip &operator[](int i) = 0; // za poziv nad nekonstantnim objektima
  virtual Tip operator[](int i) const = 0; // za poziv nad konstantnim objektima
};

//------------------------------KLASE NIZ LISTA--------------------
template <typename Tip>
class NizLista : public Lista<Tip> {
private:
    int kapacitet;
    int duzina;
    int tekuci;
    // int broj_elemenata = duzina;
    Tip **L{};
    void daLiJePrazna() const { if(duzina == 0) throw std::range_error("Lista je prazna!"); }
    void testIndeksa(int indeks) const { if(indeks < 0 || indeks >= duzina) throw std::range_error("Pogresan indeks!"); }

public:
    NizLista() : duzina(0), kapacitet(1000), tekuci(0) { L = new Tip*[kapacitet]; }
    ~NizLista() { 
        for(int i=0; i<duzina; i++) {
            delete L[i];
        }
        delete[] L; 
    }

    NizLista &operator=(NizLista &l);
    NizLista(const NizLista &l);

    inline int brojElemenata() const override { return duzina; }
    
    //-----daLiJePrazan treba provjerit za sljedece metode--------
    Tip &trenutni() override { daLiJePrazna(); return *L[tekuci]; }
    Tip trenutni() const override { daLiJePrazna(); return *L[tekuci]; }
    bool prethodni() override;
    bool sljedeci() override;
    void pocetak() override;
    void kraj() override;
    void obrisi() override;
    //-------------------------

    void dodajIspred(const Tip &el) override;
    void dodajIza(const Tip &el) override;

    Tip &operator[](int i) override; // za poziv nad nekonstantnim objektima
    Tip operator[](int i) const override; // za poziv nad konstantnim objektima
};
//------------------------------KRAJ KLASE NIZ LISTA----------------------------

template <typename Tip>
NizLista<Tip> &NizLista<Tip>::operator=(NizLista<Tip> &l) {
    if(&l == this) { // Samododjela?
        return *this;
    }
    // for(int i=0; i<this->duzina; i++) {
    //     delete L[i];
    // }
    for(int i=0; i<duzina; i++) delete L[i];
    delete[] L;
    L = new Tip*[l.kapacitet];
    duzina = l.duzina;
    kapacitet = l.kapacitet;
    tekuci = l.tekuci;
    for(int i=0; i<l.duzina; i++) {
        L[i] = new Tip(*l.L[i]);
    }
    return *this;
}
    
template <typename Tip>  
NizLista<Tip>::NizLista(const NizLista<Tip> &l) {
    kapacitet = l.kapacitet;
    duzina = l.duzina;
    tekuci = l.tekuci;
    L = new Tip*[kapacitet];
    for(int i=0; i<duzina; i++) {
        L[i] = new Tip(*l.L[i]);
    }
}

template <typename Tip>
bool NizLista<Tip>::prethodni() {
    daLiJePrazna();
    if(this->tekuci == 0) return false;
    tekuci--;
    return true;
}

template <typename Tip>
bool NizLista<Tip>::sljedeci() {
    daLiJePrazna();
    if(tekuci == duzina-1) return false;
    tekuci++;
    return true;
}

template <typename Tip>
void NizLista<Tip>::pocetak() {
    daLiJePrazna();
    tekuci = 0;
}

template <typename Tip>
void NizLista<Tip>::kraj() {
    daLiJePrazna();
    tekuci = duzina-1;
}

template <typename Tip>
void NizLista<Tip>::obrisi() {
    // std::cout << "\nDuzina jeasdwae = " << brojElemenata()<<"\n";
    daLiJePrazna();
    for(int i=(this->tekuci); i<duzina-1; i++) {
        *L[i] = *L[i+1];
    }
    // (this->duzina)--;
    duzina--;
    delete L[duzina];
    if(duzina == 0) {
        tekuci = 0;
        return;
    }
    if(tekuci == duzina) { 
        prethodni();
    }
}

template <typename Tip>
void NizLista<Tip>::dodajIza(const Tip &el) {
    if(duzina >= kapacitet - 1) { 
        Tip **temp = new Tip*[kapacitet * 2];
        for(int i=0; i<duzina; i++) {
            *temp[i] = *L[i];
            delete L[i];
        }
        delete[] L;
        kapacitet *= 2; 
        L = temp;
    }
    if(duzina == 0 && kapacitet != 0) {
        L[0] = new Tip(el);
        duzina++;
        tekuci = 0;
    } else if(duzina <= kapacitet) {
        duzina++;
        for(int i=duzina-1; i>tekuci; i--) {
            L[i] = L[i-1];
        }
        L[tekuci + 1] = new Tip(el);
    }
}

template <typename Tip>
void NizLista<Tip>::dodajIspred(const Tip &el) {
    if(duzina >= kapacitet - 1) { 
        Tip **temp = new Tip*[kapacitet * 2];
        for(int i=0; i<duzina; i++) {
            temp[i] = new Tip(*L[i]);
            delete L[i];
            L[i] = nullptr;
        }
        delete[] L;
        kapacitet *= 2; 
        L = temp;
    }
    if(duzina == 0 && kapacitet != 0) {
        //std::cout << "  asd ";
        L[duzina] = new Tip(el);
        duzina++;
        tekuci = 0;
    } else if(duzina <= kapacitet) {
        duzina++;
        for(int i=duzina-1; i>tekuci; i--) {
            L[i] = L[i - 1];
        }
        L[tekuci] = new Tip(el);
        sljedeci();
    }
}

template <typename Tip>
Tip& NizLista<Tip>::operator[](int i) {
    testIndeksa(i);
    return *L[i];
}

template <typename Tip>
Tip NizLista<Tip>::operator[](int i) const {
    testIndeksa(i);
    return *L[i];
}

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

// -----------------------------TEST---------------------------------
template <typename Tip>
void generisanjeListe(Lista<Tip> &l) {
    if(l.brojElemenata() != 0) { return; }
    for(int i=0; i<=5; i++) {
        l.dodajIspred(i);
    }
}

template <typename Tip>
void prikaziListu(Lista<Tip> &l) {
    // std::cout << " i: " << i << "  --->  " << l.trenutni() << " ";
    l.pocetak();
    for(int i=0; i<l.brojElemenata(); i++) {
        std::cout << " " << l.trenutni() << " ";
        l.sljedeci();
    }
    std::cout << "\nBROJ ELEMENATA: " <<l.brojElemenata() <<"\n";
}

template <typename TIP>
bool testBrojElemenata(Lista<TIP> &l) {
    generisanjeListe(l);
    if(l.brojElemenata() != 6) {
        std::cout << "\n\tNeispravan broj elemenata: " << l.brojElemenata() << ", a treba biti 6!";
        return false;
    }
    std::cout << "\nIspravan broj elemenata: " << l.brojElemenata() << " i treba biti 6!";
    return true;
}
  
/*
 *  ako je lista prazna, metode trenutni, prethodni, sljedeci, pocetak, kraj i
 *  obrisi trebaju baciti izuzetak;
*/

// za testiranje da li dolazi do bacanja izuzetka
template <typename Tip>
bool testIzuzetka(int n, Lista<Tip> &temp) {
    // Lista<Tip> *temp = nullptr;
    try {
        switch(n) {
            case 0:
                temp.trenutni();
                break;
            case 1:
                temp.prethodni();
                break;
            case 2:
                temp.sljedeci();
                break;
            case 3:
                temp.pocetak();
                break;
            case 4:
                temp.kraj();
                break;
            default:
                temp.obrisi();
        }
    } catch(std::range_error e) {
        e.what();
        std::cout << "Doslo je do bacanja izuzetka!\n";
        return true;
    }
    std::cout << "Nije doslo do bacanja izuzetka!\n";
    return false;
}

template <typename Tip>
void testTrenutni(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje trenutni() samo za nekonstantne liste: \n" << std::setw(10) << std::setfill('-') << "\n";
    testIzuzetka<Tip>(0, k);
    generisanjeListe(l);
    std::cout << "Trenutni element je: " << l.trenutni();

    std::cout << "\nTestiranje izmjene elementa:\n";
    l.trenutni() = 10;
    std::cout << "\tDa li je trenutni element 10: " << ((l.trenutni() == 10) ? "Jeste" : "Nije");

    std::cout << "\nElementi liste: ";
    prikaziListu(l);
    std::cout << "\nTrenutni element je: " << l.trenutni();
    std::cout << "\n" << std::setw(10) << std::setfill('-') << "\n";
}

template <typename Tip>
void testPrethodni(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje prethodni(): \n" << std::setw(10) << std::setfill('-') << "\n";
    testIzuzetka<Tip>(1,k);
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    
    std::cout << "Trenutni element je: " << l.trenutni();
    l.prethodni();
    std::cout << "\nNakon poziva prethodni(), trenutni element je: " << l.trenutni();

    std::cout << "\nZa listu od elemenata {0}: ";
    k.dodajIza(0);
    std::cout << "\n\tPravljenje nove liste i dodavanje elementa 0 uz metodu dodajIza(). Print liste: " << k.trenutni();
    std::cout << ( (k.trenutni() == 0) ? "OK" : "Trenutni od k ne daje 0" );
    // Brisanje elementa da bi lista k ostala prazna
    k.obrisi();
    std::cout << "\n" << std::setw(10) << std::setfill('-') << "\n";    
}

template <typename Tip>
void testSljedeci(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje sljedeci(): \n" << std::setw(10) << std::setfill('-') << "\n";
    testIzuzetka<Tip>(2, k);
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    
    std::cout << "Trenutni element je: " << l.trenutni();
    l.sljedeci();
    std::cout << "\nNakon poziva sljedeci(), trenutni element je: " << l.trenutni();

    std::cout << "\nZa listu od elemenata {0}: ";
    k.dodajIza(0);
    std::cout << "\n\tPravljenje nove liste i dodavanje elementa 0 uz metodu dodajIza(). Print liste: " << k.trenutni();
    std::cout << ( (k.trenutni() == 0) ? "OK" : "Trenutni od k ne daje 0" );
    // Brisanje elementa da lista k bude opet prazna
    k.obrisi();
    std::cout << "\n" << std::setw(10) << std::setfill('-') << "\n";   
}

template <typename Tip>
void testPocetak(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje pocetak(): \n" << std::setw(10) << std::setfill('-') << "\n";
    testIzuzetka<Tip>(3, k);
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    
    std::cout << "Trenutni element je: " << l.trenutni();
    l.pocetak();
    std::cout << "\nNakon poziva pocetak(), trenutni element je: " << l.trenutni();
    std::cout << "\n" << std::setw(10) << std::setfill('-') << "\n"; 
}

template <typename Tip>
void testKraj(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje kraj(): \n" << std::setw(10) << std::setfill('-') << "\n";
    testIzuzetka<Tip>(4, k);
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    // prikaziListu() stavlja da trenutni bude kraj tj trenutni ce pokazivati na zadnji element

    l.kraj();
    std::cout << "\nNakon poziva kraj(), trenutni element je: " << l.trenutni();
    std::cout << "\n" << std::setw(10) << std::setfill('-') << "\n"; 
}

template <typename Tip>
void testObrisi(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje obrisi(): \n" << std::setw(10) << std::setfill('/') << "\n";
    testIzuzetka<Tip>(5, k);
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    
    std::cout << "Trenutni element je: " << l.trenutni();
    l.obrisi();
    std::cout << "\nNakon poziva obrisi(), trenutni element je: " << l.trenutni();
    std::cout << "\nElementi liste(treba da se obrisao element): ";
    prikaziListu(l);
    std::cout << "\nSada pozivamo dva puta metodu prethodni i onda brisemo element:\n";
    l.prethodni();
    l.prethodni();
    std::cout << "\nTrenutni element je: " << l.trenutni() << "\n";
    l.obrisi();
    std::cout << "\nNakon brisanja trenutni element je: " << l.trenutni() << ", a prikaz liste:\n";
    prikaziListu(l);
    std::cout << "\n" << std::setw(10) << std::setfill('/') << "\n";
}
//----------------------------

template <typename Tip>
void testDodajIspred(Lista<Tip> &l) {
    std::cout << "\nTestiranje dodajIspred(): \n" << std::setw(10) << std::setfill('*') << "\n";
    // std::cout << "Ako je lista prazna i dodamo element sa dodajIspred(5) trenutni element je: ";
    // Lista<Tip> *nova;
    // nova->dodajIspred(5);
    // std::cout << nova->trenutni();
    std::cout << "\nGeneriranje nove liste: \n";
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    std::cout << "\nDodali element 5 s dodajIspred(), trenutni element nakon metode je: ";
    l.dodajIspred(5);
    std::cout << l.trenutni() << "\n";
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    std::cout << "\n" << std::setw(10) << std::setfill('*') << "\n";
}

template <typename Tip>
void testDodajIza(Lista<Tip> &l) {
    std::cout << "\nTestiranje dodajIza(): \n" << std::setw(10) << std::setfill('*') << "\n";
    // std::cout << "Ako je lista prazna i dodamo element sa dodajIza(5) trenutni element je: ";
    // Lista<Tip> *nova;
    // nova->dodajIza(5);
    // std::cout << nova->trenutni();
    std::cout << "\nGeneriranje nove liste:\n";
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    std::cout << "\nDodali element 7 s dodajIza(), trenutni element nakon metode je: ";
    l.dodajIza(7);
    std::cout << l.trenutni() << "\n";
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    std::cout << "\n" << std::setw(10) << std::setfill('*') << "\n";
}

// predavanje 11a strana 3
template <typename Tip>
void testOperatoraUglasteZagrade(Lista<Tip> &l) {
    std::cout << "\nTestiranje operator[](): \n" << std::setw(10) << std::setfill('#') << "\n";
    generisanjeListe(l);
    prikaziListu(l);
    try {
        l[-1];
    } catch(std::range_error e) {
        std::cout << "\nIndeks je -1: " << e.what();
    }
    try {
        l[l.brojElemenata() + 1];
    } catch(std::range_error e) {
        std::cout << "\nIndeks je brElemenata + 1: " << e.what() << "\n";
    }
    std::cout << "Elementi niza unazad:\n";
    for(int i=l.brojElemenata() - 1; i >= 0; i--) {
        std::cout << " " << l[i] << "\t";
    }
    std::cout << "\nElement s indeksom 3(dakle 4 element) je " << l[3];
    l[3] = 9;
    std::cout << ", a nakon izmjene da li je 9? " << l[3] << "\n";
    std::cout << "Elementi niza naprijed:\n";
    for(int i=0; i < l.brojElemenata(); i++) {
        std::cout << " " << l[i] << "\t";
    }
    std::cout << "\n" << std::setw(10) << std::setfill('#') << "\n";
}

template <typename Tip>
void mainTest(Lista<Tip> &l, Lista<Tip> &k) {
    /*
        generirajPraznuListu(l) prvo trebamo pozvati da testiramo 
        implementaciju i nad praznom listom, a izmedju ostalog i operator dodjele
    */
    // generirajPraznuListu(l);
    testBrojElemenata(l);
    testTrenutni(l, k);
    testPrethodni(l, k);
    testSljedeci(l, k);
    testPocetak(l, k);
    testKraj(l, k);
    testObrisi(l, k);
    testDodajIspred(l);
    testDodajIza(l);
    testOperatoraUglasteZagrade(l);
    std::cout << "\n\tKRAJ TESTIRANJA";
}
// -----------------------------KRAJ TEST-a---------------------------------

int main() {
    NizLista<int> *niz_lista = new NizLista<int>;
    NizLista<int> *prazna_lista_k = new NizLista<int>;
    mainTest(*niz_lista, *prazna_lista_k);
    JednostrukaLista<int> *l = new JednostrukaLista<int>;
    JednostrukaLista<int> *p = new JednostrukaLista<int>;
    mainTest(*l, *p);
    return 0;
}

// using namespace std;

// int main() {
    // JednostrukaLista<int> lista;
    // for (int i(1); i<=5; i++)
    //     lista.dodajIspred(i);
    // {
    //     JednostrukaLista<int> lista2(lista);
    //     JednostrukaLista<int> lista3;
    //     lista3=lista;
    //     lista.obrisi();
    //     std::cout << lista2.brojElemenata();
    //     std::cout << " " << lista3.brojElemenata() << " ";
    // }
    // std::cout << lista.brojElemenata();
                    
//     return 0;
// }