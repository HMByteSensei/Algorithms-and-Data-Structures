#include <iostream>
#include <new>
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

//------------------------------KLASA DvostrukaLista LISTA--------------------
template <typename Tip>
class DvostrukaLista : public Lista<Tip> {
private:
    int duzina;
    struct Cvor {
        Tip element; // predavanje 8b
        Cvor *sljedeci;
        Cvor *predhodni;
    };
    Cvor *pocetak_liste = nullptr;
    Cvor *kraj_liste = nullptr;
    Cvor *tekuci;

    void daLiJePrazna() const { if(pocetak_liste == nullptr) throw std::range_error("Lista je prazna!"); }
    void TestIndeksa(int indeks) const { if(indeks < 0 || indeks >= duzina) throw std::range_error("Indeks je van opsega!"); }

public:
    DvostrukaLista() : duzina(0) { pocetak_liste = nullptr; tekuci = nullptr; kraj_liste = nullptr; }
    ~DvostrukaLista();

    DvostrukaLista(const DvostrukaLista &l);
    DvostrukaLista &operator=(const DvostrukaLista &l);

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
DvostrukaLista<Tip>::DvostrukaLista(const DvostrukaLista<Tip> &l) {
    duzina = 0;
    pocetak_liste = kraj_liste = tekuci =  nullptr;
    Cvor *temp = l.pocetak_liste;
    while(temp != nullptr) {
        // Cvor *novi = new Cvor{temp->element, nullptr, nullptr};
        // if(pocetak_liste == nullptr) {
        //     pocetak_liste = kraj_liste = tekuci = novi;
        // }
        dodajIza(temp->element);
        sljedeci();
        temp = temp->sljedeci;
    }
}

template <typename Tip>
DvostrukaLista<Tip> &DvostrukaLista<Tip>::operator=(const DvostrukaLista &l) {
    if(&l == this) return *this; // Samododjela?
    DvostrukaLista<Tip> temp(l);
    duzina = l.duzina;
    std::swap(tekuci, temp.tekuci);
    std::swap(kraj_liste, temp.kraj_liste);
    std::swap(pocetak_liste, temp.pocetak_liste);
    return *this;
}

template <typename Tip>
DvostrukaLista<Tip>::~DvostrukaLista() {
    while(pocetak_liste != nullptr) {
        Cvor *temp = pocetak_liste;
        pocetak_liste = pocetak_liste->sljedeci;
        delete temp;
    }
    pocetak_liste = nullptr;
    kraj_liste = nullptr;
    tekuci = nullptr;
    duzina = 0;
}

template <typename Tip>
Tip& DvostrukaLista<Tip>::trenutni() {
    daLiJePrazna();
    return tekuci->element;
}

template <typename Tip>
Tip DvostrukaLista<Tip>::trenutni() const {
    daLiJePrazna();
    return tekuci->element;
}

template <typename Tip>
bool DvostrukaLista<Tip>::prethodni() {
    daLiJePrazna();
    if(tekuci == pocetak_liste) return false;
    tekuci = tekuci->predhodni;
    return true;
}

template <typename Tip>
bool DvostrukaLista<Tip>::sljedeci()  {
    daLiJePrazna();
    if(tekuci->sljedeci == nullptr) return false;
    tekuci = tekuci->sljedeci;
    return true;
}

template <typename Tip>
void DvostrukaLista<Tip>::pocetak() {
    daLiJePrazna();
    tekuci = pocetak_liste;
}

template <typename Tip>
void DvostrukaLista<Tip>::kraj() {
    daLiJePrazna();
    tekuci = kraj_liste;
}

template <typename Tip>
void DvostrukaLista<Tip>::obrisi() {
    daLiJePrazna();
    //if(duzina - 1 == 0) { cvor_prije = nullptr; }
    if(tekuci == pocetak_liste) {
        // std::cout << "\nTEKUCI->sljedeci = " << cvor_prije;
        if(duzina == 1) { /// ako imamo samo 1 element
            delete tekuci;
            tekuci = nullptr;
            kraj_liste = nullptr;
            pocetak_liste = nullptr;
            duzina--;
        } else {
            pocetak_liste = pocetak_liste->sljedeci;
            delete tekuci;
            tekuci = pocetak_liste;
            pocetak_liste->predhodni = nullptr;
            duzina--;
        }
    } else {
        if(tekuci != kraj_liste) {
            Cvor *temp = tekuci->sljedeci;
            tekuci->predhodni->sljedeci = temp;
            temp->predhodni = tekuci->predhodni;
            delete tekuci;
            tekuci = temp;
        } else {
            Cvor *temp = tekuci->predhodni;
            delete tekuci;
            tekuci = temp;
            kraj_liste = temp;
            tekuci->sljedeci = nullptr;
        }
        duzina--;
    }
}

template <typename Tip>
void DvostrukaLista<Tip>::dodajIza(const Tip &el) {
    if(pocetak_liste == nullptr) {              // tj ako lista nema elemenata
        pocetak_liste = new Cvor{el, nullptr, nullptr};
        tekuci = pocetak_liste;
        kraj_liste = pocetak_liste;
    } else {
        Cvor *novi = new Cvor{el, tekuci->sljedeci, tekuci};
        tekuci->sljedeci = novi;
        if(novi->sljedeci != nullptr) {
            novi->sljedeci->predhodni = novi;
        } else {
            kraj_liste = novi;
        }
    }
    duzina++;
}

template <typename Tip>
void DvostrukaLista<Tip>::dodajIspred(const Tip &el) {
    if(pocetak_liste == nullptr) { // nemamo elemenata u listi
        pocetak_liste = new Cvor{el, nullptr, nullptr};
        tekuci = pocetak_liste;
        kraj_liste = tekuci;
    } else {
        if(tekuci == pocetak_liste) {
            Cvor *novi = new Cvor{el, pocetak_liste, nullptr};
            //kraj_liste = pocetak_liste;
            tekuci->predhodni = novi;
            pocetak_liste = novi;
        } else {
            Cvor *novi = new Cvor{el, tekuci, tekuci->predhodni};
            tekuci->predhodni = novi;
            novi->predhodni->sljedeci = novi;
        }
    }
    duzina++;
}

template <typename Tip>
Tip& DvostrukaLista<Tip>::operator[](int indeks) {
    TestIndeksa(indeks); // provjera da li je indeks uredu
    Cvor *temp = pocetak_liste;
    for(int i=0; i<indeks; i++) {
        temp = temp->sljedeci;
    }
    return temp->element;
    // // predpostavka je da se duzina povecava s dodavanjem broja elemenata
    // // pa ako je TestIndeksa prosao to znaci da Lista nije prazna
    // cvor_prije = pocetak_liste;
    // for(int i=0; i<indeks-1; i++) { // do indeks-1 jer smo vec stavili cvor_prije na pocetak pa je cvor_prije brzi za 1
    //     cvor_prije = cvor_prije->sljedeci;
    // }
    // tekuci = cvor_prije->sljedeci;
    // return tekuci->element;
}

template <typename Tip>
Tip DvostrukaLista<Tip>::operator[](int indeks) const {
    TestIndeksa(indeks);
    Cvor *temp = pocetak_liste;
    for(int i=0; i<indeks; i++) {
        temp = temp->sljedeci;
    }
    return temp->element;
}

//IMPLEMENTACIJA TRAZENE FUNKCIJE
template<typename Tip>
Tip dajMaksimum(const Lista<Tip>& n) {
    DvostrukaLista<Tip> dvostruka = static_cast<DvostrukaLista<Tip>&>(const_cast<Lista<Tip>&>(n));
    dvostruka.pocetak();
    Tip max = dvostruka.trenutni();
    dvostruka.sljedeci();
    for(int i=0; i<dvostruka.brojElemenata()-1; i++) {
        if(max < dvostruka.trenutni()) {
            max = dvostruka.trenutni();
        }
        dvostruka.sljedeci();
    }
    return max;
}


//KRAJ IMPLEMENTACIJE TRAZENE FUNKCIJE

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

//TEST ZA TU FUNKCIJU
template<typename Tip>
void testDajMaksimum(DvostrukaLista<Tip> &n) {
    std::cout << "\nNajveci element je: " << dajMaksimum(n);
}

// za autotest 16
using namespace std;

int main() {
    DvostrukaLista<int> *l = new DvostrukaLista<int>;
    DvostrukaLista<int> *prazna_lista_k = new DvostrukaLista<int>;
    mainTest(*l, *prazna_lista_k);

    // Specijalno test za trazenu funkciju
    testDajMaksimum(*l);
    return 0;
}