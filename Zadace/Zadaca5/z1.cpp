#include <iostream>
#include <stdexcept>
#include <functional>
#include <random>
#include <vector>
#include <tuple>
#include <queue>
#include<string>

using namespace std;

template <typename Kljuc, typename Vrijednost>
class Mapa {
public:
    Mapa() {};
    virtual ~Mapa() {};
    virtual Vrijednost &operator[](const Kljuc &k) = 0;
    virtual Vrijednost operator[](const Kljuc &k) const = 0;
    virtual int brojElemenata() const = 0;
    virtual void obrisi() = 0;
    virtual void obrisi(const Kljuc &kljuc) = 0;
};

template <typename Kljuc, typename Vrijednost>
class HashMapaLan : public Mapa<Kljuc, Vrijednost> {
private:
    unsigned int kapacitet;
    int brElemenata;
    unsigned int pocetniKapacitet;
    //unsigned int (*zadanHash)(const Kljuc &, unsigned int)=nullptr; // signalizira da nema hash fije
    std::function<unsigned int(const Kljuc&, unsigned int)> zadanHash=nullptr;
    std::vector<std::pair<Kljuc, std::pair<Vrijednost, bool>>> *niz;
    unsigned int hashFunkcija(const Kljuc &k, unsigned int i = 10) const {
        return (zadanHash(k, pocetniKapacitet) + i) % pocetniKapacitet;
    }

public:
    HashMapaLan() : kapacitet(1000), brElemenata(0), pocetniKapacitet(kapacitet) {
        niz = new std::vector<std::pair<Kljuc, std::pair<Vrijednost, bool>>>[kapacitet]{};
    };
    ~HashMapaLan() { delete[] niz; };
    HashMapaLan(const HashMapaLan<Kljuc, Vrijednost> &n);
    HashMapaLan<Kljuc, Vrijednost> &operator=(const HashMapaLan &n);
    Vrijednost &operator[](const Kljuc &k) override;
    Vrijednost operator[](const Kljuc &k) const override;
    int brojElemenata() const override;
    void obrisi() override;
    void obrisi(const Kljuc &kljuc) override; 
    //template<typename H>
    void definisiHashFunkciju(std::function<unsigned int(const Kljuc&, unsigned int)> zadanHash) {
        this->zadanHash = zadanHash;
    }
};

template <typename Kljuc, typename Vrijednost>
Vrijednost &HashMapaLan<Kljuc, Vrijednost>::operator[](const Kljuc &k) {
    if(!zadanHash) {
        throw std::logic_error("Niste unijeli hash funkciju.");
    } 
    if(brElemenata == kapacitet) {
        std::vector<std::pair<Kljuc, std::pair<Vrijednost, bool>>> *novi = new std::vector<std::pair<Kljuc, std::pair<Vrijednost, bool>>>[kapacitet * 2]{};
        for(int i=0; i<kapacitet; i++) {
            for(int j=0; j<novi[i].size(); j++) {
                novi[i].at(j).first = niz[i].at(j).first;
                novi[i].at(j).second = niz[i].at(j).second;
            }
        }
        delete[] niz;
        niz = novi;
        kapacitet *= 2;
        novi = nullptr;
    }
    unsigned int hashIndex;
    int i=0;
    int poz{};
    do {
        hashIndex = hashFunkcija(k, i);
        poz = 0;
        for(int j=0; j<niz[hashIndex].size(); j++) {
            if(k == niz[hashIndex].at(j).first) {
                return niz[hashIndex].at(j).second.first;
            }
            if(niz[hashIndex].at(j).first == Kljuc{} && niz[hashIndex].at(j).second.first == Vrijednost{} && niz[hashIndex].at(j).second.second == false) {
                poz = j;
                break;
            }
        }
        i++;
    } while(i<=brElemenata);

    //std::cout << "\nFija vraca: " << hashIndex << " za kljuc: " << k;
    niz[hashIndex].push_back({}); 
    niz[hashIndex].at(poz).first = k;
    niz[hashIndex].at(poz).second.first = Vrijednost();
    brElemenata++;
    return niz[hashIndex].at(poz).second.first;
}

template <typename Kljuc, typename Vrijednost>
Vrijednost HashMapaLan<Kljuc, Vrijednost>::operator[](const Kljuc &k) const {
    if(!zadanHash) {
        throw std::logic_error("Niste unijeli hash funkciju.");
    }
    unsigned int hashIndex = hashFunkcija(k, 0);
    for(int i=0; i<brElemenata; i++) {
        hashIndex = hashFunkcija(k, i);
        for(int j=0; j<niz[hashIndex].size(); j++) {
            if(k == niz[hashIndex].at(j).first) {
                return niz[hashIndex].at(j).second.first;
            }
            // (0, 0) signalizira da ovo polje nije nikada ni bilo popunjeno
            if(niz[hashIndex].at(j).first == (Kljuc{}) && niz[hashIndex].at(j).second.first == (Vrijednost{}) && !niz[hashIndex].at(j).second.second) {
                break;
            }
        }
    }
    return Vrijednost{};
}

template <typename Kljuc, typename Vrijednost>
int HashMapaLan<Kljuc, Vrijednost>::brojElemenata() const {
    return brElemenata;
}

template <typename Kljuc, typename Vrijednost>
void HashMapaLan<Kljuc, Vrijednost>::obrisi() {
    kapacitet /= 4;
    brElemenata = 0;
    delete[] niz;
    niz = new std::vector<std::pair<Kljuc, std::pair<Vrijednost, bool>>>[kapacitet]{};
}

template <typename Kljuc, typename Vrijednost>
void HashMapaLan<Kljuc, Vrijednost>::obrisi(const Kljuc &k) {
    unsigned int index = hashFunkcija(k, 0); 
    // ako je br elemenata 0 for se ne izvrsi
    for(int i=0; i<brElemenata; i++) {
        index = hashFunkcija(k, i);
        for(int j=0; j<niz[index].size(); j++) {
            if(niz[index].at(j).first == k) {
                // oznaka da je obrisan element
                niz[index].at(j).second.second = true;
                niz[index].at(j).first = Kljuc{};
                niz[index].at(j).second.first = Vrijednost{};
                brElemenata--;
                //std::cout << "\n\t#Obrisan element: " << k << " index: " << index;
                return;
            } 
        }
    }
    throw std::invalid_argument("Trazeni element ne postoji u mapi");
}

template <typename Kljuc, typename Vrijednost>
HashMapaLan<Kljuc, Vrijednost>::HashMapaLan(const HashMapaLan<Kljuc, Vrijednost> &n) {
    kapacitet = n.kapacitet;
    brElemenata = n.brElemenata;
    pocetniKapacitet = n.pocetniKapacitet;
    zadanHash = n.zadanHash;
    niz = new std::vector<std::pair<Kljuc, std::pair<Vrijednost, bool>>>[n.kapacitet]{};
    for(int i=0; i<kapacitet; i++) {
        for(int j=0; j<niz[i].size(); j++) {
            niz[i].at(j).first = n.niz[i].at(j).first;
            niz[i].at(j).second.first = n.niz[i].at(j).second.first;
            niz[i].at(j).second.second = n.niz[i].at(j).second.second;
        }
    }
}

template<typename Kljuc, typename Vrijednost>
HashMapaLan<Kljuc, Vrijednost> &HashMapaLan<Kljuc, Vrijednost>::operator=(const HashMapaLan<Kljuc, Vrijednost> &n) {
    if(this == &n) {
        return *this;
    }
    delete[] niz;
    kapacitet = n.kapacitet;
    brElemenata = n.brElemenata;
    pocetniKapacitet = n.pocetniKapacitet;
    niz = new std::vector<std::pair<Kljuc, std::pair<Vrijednost, bool>>>[n.kapacitet]{};
    zadanHash = n.zadanHash;
    for(int i=0; i<kapacitet; i++) {
        for(int j=0; j<niz[i].size(); j++) {
            niz[i].at(j).first = n.niz[i].at(j).first;
            niz[i].at(j).second.first = n.niz[i].at(j).second.first;
            niz[i].at(j).second.second = n.niz[i].at(j).second.second;
        }
    }
    return *this;
}

unsigned int hashFija(int ulaz, unsigned int max) {
    return std::hash<int>{}(ulaz);
}

// ne dopusta se da dva cvora imaju vise od jedne grane
template <typename Tip>
class Grana;

template <typename Tip>
class Cvor;

template <typename Tip>
class UsmjereniGraf;

template <typename TipOznake>
class GranaIterator {
    UsmjereniGraf<TipOznake> *ug;
    int pocetna_poz, krajnja_poz;
    //int brojac_inkrementacija;
    GranaIterator() {}
public:
    GranaIterator(UsmjereniGraf<TipOznake> *graf, int poc, int kraj) {
        ug = graf;
        pocetna_poz = poc;
        krajnja_poz = kraj;
        //brojac_inkrementacija = 0;
    }
    Grana<TipOznake> operator*() {return ug->dajGranu(pocetna_poz, krajnja_poz); }
    bool operator==(const GranaIterator &iter) { return &iter == this; }
    bool operator!=(const GranaIterator &iter) { return &iter != this; }
    GranaIterator& operator++() {
        do {
            
            if(krajnja_poz >= ug->dajBrojCvorova()) {
                pocetna_poz++;
                krajnja_poz = 0;
            }
            krajnja_poz++;
        } while(!ug->postojiGrana(pocetna_poz, krajnja_poz) && pocetna_poz >= ug->dajBrojCvorova());
        // if((++brojac_inkrementacija) >= ug->dajBroj);
        return *this;
    }
    GranaIterator operator++(int) {
        GranaIterator<TipOznake> kopija(*this);
        this->operator++();
        return kopija;
    }
};

template <typename Tip>
class UsmjereniGraf {
private:
    int brojCvorova;
    mutable bool pocetak = false;
public:
    UsmjereniGraf<Tip>() {};
    UsmjereniGraf(int brojCvorova) { this->brojCvorova = brojCvorova; }
    virtual int dajBrojCvorova() const = 0;
    
    virtual ~UsmjereniGraf(){};
    virtual void postaviBrojCvorova(int br) = 0;
    virtual void dodajGranu(int polazni, int dolazni, double tezina) = 0;
    virtual void obrisiGranu(int polazni, int dolazni) = 0;
    virtual void postaviTezinuGrane(int polazni, int dolazni, double tezina)  = 0;
    
    virtual double dajTezinuGrane(int polazni, int krajnji) = 0;
    virtual bool postojiGrana(int pocetni, int krajnji) const = 0;

    // vraca true ako se uspjesno postavila oznaka
    virtual void postaviOznakuCvora(int pozicija_cvora, Tip oznaka) = 0;
    virtual void postaviOznakuGrane(int pocetni, int krajnji, Tip oznaka) = 0;
    
    virtual Tip dajOznakuCvora(int pozicija_cvora) = 0;
    virtual Tip dajOznakuGrane(int pocetni, int krajnji) = 0;

    virtual Grana<Tip>dajGranu(int pocetniCvor, int krajnjiCvor) = 0;
    virtual Cvor<Tip> dajCvor(int pozicija) = 0;

    virtual GranaIterator<Tip> dajGranePocetak() = 0;

    virtual GranaIterator<Tip> dajGraneKraj()=0;
};



template <typename Tip>
class Grana {
    UsmjereniGraf<Tip> *ug;
    int pocetnaPozicija, krajnjaPozicija;
public: 
    Grana(UsmjereniGraf<Tip> *graf, int poc, int kraj) : ug(graf), pocetnaPozicija(poc), krajnjaPozicija(kraj) {}

    double dajTezinu() const { return ug->dajTezinuGrane(pocetnaPozicija, krajnjaPozicija);}
    Tip dajOznaku() const {
        return ug->dajOznakuGrane(pocetnaPozicija, krajnjaPozicija);
    }
    void postaviTezinu(double tezina) {
        ug->postaviTezinuGrane(pocetnaPozicija, krajnjaPozicija);
    }
    void postaviOznaku(Tip oznaka) {
        ug->postaviOznakuGrane(pocetnaPozicija, krajnjaPozicija, oznaka);
    }
    Cvor<Tip> dajPolazniCvor() const {return ug->dajCvor(pocetnaPozicija);} 
    Cvor<Tip> dajDolazniCvor() const {
        return ug->dajCvor(krajnjaPozicija);
    }
};

template <typename Tip>
class Cvor {
private:
    int redni_broj;
    UsmjereniGraf<Tip> *ug;
public:
    Cvor(UsmjereniGraf<Tip> *graf, int redniBrCvora) : ug(graf), redni_broj(redniBrCvora) {};
    
    Tip dajOznaku() const {return ug->dajOznakuCvora(redni_broj);}
    void postaviOznaku(Tip oznaka) {
        ug->postaviOznakuCvora(redni_broj, oznaka);
    }
    int dajRedniBroj() const {return redni_broj;}
};

template<typename Tip>
class MatricaGraf : public UsmjereniGraf<Tip> {
private:
    int brojCvorova;
    // bool = da li je povezano ili ne, double je tezina grane, Tip = oznaka 
    std::vector<std::vector<std::tuple<bool, double, Tip>>> matrica;
    std::vector<Tip> oznakaCvora;
public:
    MatricaGraf(int broj) : matrica(broj, std::vector<std::tuple<bool, double, Tip>>(broj, std::make_tuple(false, 0.0f, Tip{}))), oznakaCvora(broj) {
        brojCvorova = broj;
    }
    MatricaGraf() {};
    ~MatricaGraf(){};
    int dajBrojCvorova() const override {
        return oznakaCvora.size();
    }
    void postaviBrojCvorova(int br) override {
        if(br < brojCvorova) {
            throw std::domain_error("Nije dozvoljeno da postavite manji broj cvorova od postojeceg");
        }
        matrica.resize(br);
        for(int i=brojCvorova; i<br; i++) {
            matrica.at(i).resize(br, std::make_tuple(false, 0.0f, Tip{}));
        }
        brojCvorova = br;
    }
    void dodajGranu(int polazni, int dolazni, double tezina) override {
        matrica.at(polazni).at(dolazni) = std::make_tuple(true, tezina, Tip{});
    }
    void obrisiGranu(int polazni, int dolazni) override {
        // samo oznacima da nije povezana grana
        std::get<0>(matrica.at(polazni).at(dolazni)) = false;
    }
    void postaviTezinuGrane(int polazni, int dolazni, double tezina) override {
        std::get<1>(matrica.at(polazni).at(dolazni)) = tezina;
    }

    double dajTezinuGrane(int polazni, int krajnji) const override {
        return std::get<1>(matrica.at(polazni).at(krajnji));
    }
    bool postojiGrana(int pocetni, int krajnji) const override {
        return std::get<0>(matrica.at(pocetni).at(krajnji));
    }

// vraca true ako se uspjesno postavila oznaka
    void postaviOznakuCvora(int pozicija_cvora, Tip oznaka) override {
        oznakaCvora.at(pozicija_cvora) = oznaka;
    }
    void postaviOznakuGrane(int pocetni, int krajnji, Tip oznaka) override {
        std::get<2>(matrica.at(pocetni).at(krajnji)) = oznaka;
    }

    Tip dajOznakuCvora(int pozicija_cvora) override {
        return oznakaCvora.at(pozicija_cvora);
    }
    Tip dajOznakuGrane(int pocetni, int krajnji) const override {
        return std::get<2>(matrica.at(pocetni).at(krajnji));
    }

    Grana<Tip>dajGranu(int pocetniCvor, int krajnjiCvor) override {
        return Grana<Tip>(this, pocetniCvor, krajnjiCvor);
    }
    Cvor<Tip> dajCvor(int pozicija) override {
        if(pozicija < 0 || pozicija >= dajBrojCvorova()) {
            throw std::range_error("Pozicija izvan opsega");
        }
        return Cvor<Tip>(this, pozicija);
    }
};

template <typename Tip>
class ListaGraf : public UsmjereniGraf<Tip> {
    std::vector<std::vector<tuple<Tip, double, bool>>> lista;
    std::vector<Tip> oznaka;
public:
    ListaGraf(int br) : UsmjereniGraf<Tip>(br){
        postaviBrojCvorova(br);
    }
    int dajBrojCvorova() const override {
        return lista.size();
    };

    void postaviBrojCvorova(int br) override {
        for(int i=0; i<lista.size(); i++) {
            lista[i].resize(br, {Tip{}, 0.0f, false});
        }
        std::vector<std::tuple<Tip, double, bool>> novi(br, {Tip{}, 0.0f, false});
        lista.resize(br, novi);
        oznaka.resize(br);
    }
    void dodajGranu(int polazni, int dolazni, double tezina) override {
        lista.at(polazni).at(dolazni) = std::make_tuple(Tip{}, tezina, true); 
    }
    void obrisiGranu(int polazni, int dolazni) override {
        get<2>(lista.at(polazni).at(dolazni)) = false;
    }
    void postaviTezinuGrane(int polazni, int dolazni, double tezina) override {
        get<1>(lista.at(polazni).at(dolazni)) = tezina;
    }
    
    double dajTezinuGrane(int polazni, int krajnji) override {
        return get<1>(lista.at(polazni).at(krajnji));
    }
    bool postojiGrana(int pocetni, int krajnji) const override {
        return get<2>(lista.at(pocetni).at(krajnji));
    }

    // vraca true ako se uspjesno postavila oznaka
    void postaviOznakuCvora(int pozicija_cvora, Tip o) override {
        oznaka.at(pozicija_cvora) = o;
    }
    void postaviOznakuGrane(int pocetni, int krajnji, Tip oznaka) override {
        get<0>(lista.at(pocetni).at(krajnji)) = oznaka;
    }
    
    virtual Tip dajOznakuCvora(int pozicija_cvora) override {
        return oznaka.at(pozicija_cvora);
    }
    Tip dajOznakuGrane(int pocetni, int krajnji) override {
        return get<0>(lista.at(pocetni).at(krajnji));
    }

    GranaIterator<Tip> dajGranePocetak() override {
        GranaIterator<Tip> iter(this, 0, -1);
        return (++iter);
    } 
    GranaIterator<Tip> dajGraneKraj() override{
        return GranaIterator<Tip>(this, -1, -1);
    }
    Grana<Tip>dajGranu(int pocetniCvor, int krajnjiCvor) override {
        return Grana<Tip>(this, pocetniCvor, krajnjiCvor);
    }
    Cvor<Tip> dajCvor(int pozicija) override {
        return Cvor<Tip>(this, pozicija);
    }

};

// BFS
template<typename Tip>
void recursiveBFS(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, std::queue<Cvor<Tip>> &q);

template <typename Tip>
void bfs(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, Cvor<Tip> cvor) {
    cvor.postaviOznaku(1);
    obilazak.push_back(cvor);
    std::queue<Cvor<Tip>> red;
    red.push(cvor);
    recursiveBFS(ug, obilazak, red);
}

template<typename Tip>
void recursiveBFS(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, std::queue<Cvor<Tip>> &q) {
    if(q.empty()) {
        return;
    }
    Cvor<Tip> c = q.front();
    q.pop();
    obradiSusjedni(ug, obilazak, q, c);

    recursiveBFS(ug, obilazak, q);
}

template<typename Tip>
void obradiSusjedni(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, std::queue<Cvor<Tip>> &q, Cvor<Tip> c) {
    GranaIterator<Tip> grana = ug->dajGranePocetak();

    for(auto pom = grana; pom != ug->dajGraneKraj(); pom++) {
        auto start = (*pom).dajPolazniCvor();
        auto end = (*pom).dajDolazniCvor();
    
        if(end.dajOznaku() != 1 && start.dajRedniBroj() == c.dajRedniBroj()) {
            end.postaviOznaku(1);
            obilazak.push_back(end);
            q.push(end);
        }
    }
}

//DFS
template<typename Tip>
void dfs(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, Cvor<Tip> c) {
    c.postaviOznaku(1);
    obilazak.push_back(c);
    for(GranaIterator<Tip> iter = ug->dajGranePocetak(); iter != ug->dajGraneKraj(); iter++) {
        if((*iter).dajPolazniCvor().dajRedniBroj() == c.dajRedniBroj() && (*iter).dajDolazniCvor().dajOznaku() != 1) {
            dfs(ug, obilazak, (*iter).dajDolazniCvor());
        }
    }
}









int main() {
   UsmjereniGraf<std::string> *g = new ListaGraf<std::string>(4);
  g->dodajGranu(0, 1, 2.5);
  g->dodajGranu(1, 2, 1.2);
  g->dodajGranu(1, 3, 0.1);
  g->dodajGranu(3, 3, -4.0);
  g->postaviOznakuGrane(3, 3, "aa");
  g->dajGranu(0,1).postaviOznaku("bb");
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (g->postojiGrana(i,j))
        cout << "(" << i << "," << j << ") -> '" << g->dajOznakuGrane(i, j) << "','" << g->dajGranu(i, j).dajOznaku() << "'; ";
delete g;
    return 0;
}