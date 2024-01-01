#include "zadatak1.h"
#include "test.h"

#include <stdexcept>

// kapaciacitet *= 2

template <typename Tip>
class NizLista : public Lista<Tip> {
private:
    int kapacitet;
    int duzina;
    int tekuci;
    // int broj_elemenata = duzina;
    Tip* L;
    void daLiJePrazna() const { if(duzina == 0) throw std::range_error("Lista je prazna!"); }
    void testIndeksa(int indeks) const { if(indeks < 0 || indeks >= duzina) throw std::range_error("Pogresan indeks!"); }

public:
    NizLista() : duzina(0), kapacitet(1000), tekuci(0) { L = new Tip[kapacitet]; }
    ~NizLista() { delete[] L; }

    NizLista &operator=(NizLista &l);
    NizLista(const NizLista &l);

    inline int brojElemenata() const override { return duzina; }
    
    //-----daLiJePrazan treba provjerit za sljedece metode--------
    Tip &trenutni() override { daLiJePrazna(); return L[tekuci]; }
    Tip trenutni() const override { daLiJePrazna(); return L[tekuci]; }
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

template <typename Tip>
NizLista<Tip> &NizLista<Tip>::operator=(NizLista<Tip> &l) {
    if(&l == this) { // Samododjela?
        return *this;
    }
    for(int i=0; i<this->duzina; i++) {
        delete L[i];
    }
    delete[] L;
    L = new Tip *[l.kapacitet];
    this->duzina = l.duzina;
    this->kapacitet = l.kapacitet;
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
    L = new Tip[kapacitet];
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
    daLiJePrazna();
    for(int i=(this->tekuci); i<duzina; i++) {
        L[i] = L[i+1];
    }
    // (this->duzina)--;
    /* 
        PROVJERIT DOBRO smanjili smo duzinu za 1 sto znaci izbacili smo zadnji element, pa gledamo da li je tekuci == duzina 
        buduci da tekuci pocinje od 0 a duzina od 1, tj tekuci je indexx elementa, a duzina je broj elemenata u NizListi 
    */
    if(tekuci == (--duzina)) { 
        prethodni();
    }
}

template <typename Tip>
void NizLista<Tip>::dodajIspred(const Tip &el) {
    if(duzina == kapacitet - 1) { kapacitet *= 2; }
    if(duzina == 0 && kapacitet != 0) {
        L[0] = el;
        duzina++;
        tekuci = 0;
    } else if(duzina <= kapacitet) {
        duzina++;
        for(int i=duzina-1; i>tekuci; i--) {
            L[i] = L[i-1];
        }
        L[tekuci + 1] = el;
    }
}

template <typename Tip>
void NizLista<Tip>::dodajIza(const Tip &el) {
    if(duzina == kapacitet - 1) { kapacitet *= 2; }
    if(duzina == 0 && kapacitet != 0) {
        L[duzina] = el;
        duzina++;
        tekuci = 0;
    }
    if(duzina < kapacitet) {
        duzina++;
        for(int i=duzina-1; i>=tekuci; i--) {
            L[i+1] = L[i];
        }
        L[tekuci] = el;
        sljedeci();
    }
}

template <typename Tip>
Tip& NizLista<Tip>::operator[](int i) {
    testIndeksa(i);
    return L[i];
}

template <typename Tip>
Tip NizLista<Tip>::operator[](int i) const {
    testIndeksa(i);
    return L[i];
}

int main() {
    NizLista<int> *niz_lista = new NizLista<int>;
    NizLista<int> *prazna_lista_k = new NizLista<int>;
    mainTest(*niz_lista, *prazna_lista_k);
    return 0;
}