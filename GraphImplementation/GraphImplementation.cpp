#include <iostream>
#include <stdexcept>
#include <vector>
#include <tuple>
#include <queue>
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
    virtual void dodajGranu(int polazni, int dolazni, float tezina) = 0;
    virtual void obrisiGranu(int polazni, int dolazni) = 0;
    virtual void postaviTezinuGrane(int polazni, int dolazni, float tezina)  = 0;
    
    virtual float dajTezinuGrane(int polazni, int krajnji) const = 0;
    virtual bool postojiGrana(int pocetni, int krajnji) const = 0;

    // vraca true ako se uspjesno postavila oznaka
    virtual void postaviOznakuCvora(int pozicija_cvora, Tip oznaka) = 0;
    virtual void postaviOznakuGrane(int pocetni, int krajnji, Tip oznaka) = 0;
    
    virtual Tip dajOznakuCvora(int pozicija_cvora) = 0;
    virtual Tip dajOznakuGrane(int pocetni, int krajnji) const = 0;

    virtual Grana<Tip>dajGranu(int pocetniCvor, int krajnjiCvor) = 0;
    virtual Cvor<Tip> dajCvor(int pozicija) = 0;

    virtual GranaIterator<Tip> dajGranePocetak() {
        if(!pocetak) {
            pocetak = true;
            return ++GranaIterator<Tip>(this, 0, this->dajBrojCvorova());
        }
        return ++GranaIterator<Tip>(this, 0, -1);
    } 
    virtual GranaIterator<Tip> dajGraneKraj() {
        return GranaIterator<Tip>(this, this->dajBrojCvorova(), 0);
    }
};


template <typename Tip>
class Grana {
    UsmjereniGraf<Tip> *ug;
    int pocetnaPozicija, krajnjaPozicija;
public: 
    Grana(UsmjereniGraf<Tip> *graf, int poc, int kraj) : ug(graf), pocetnaPozicija(poc), krajnjaPozicija(kraj) {}

    float dajTezinu() const { return ug->dajTezinuGrane(pocetnaPozicija, krajnjaPozicija);}
    Tip dajOznaku() const {
        return ug->dajOznakuGrane(pocetnaPozicija, krajnjaPozicija);
    }
    void postaviTezinu(float tezina) {
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
    // bool = da li je povezano ili ne, float je tezina grane, Tip = oznaka 
    std::vector<std::vector<std::tuple<bool, float, Tip>>> matrica;
    std::vector<Tip> oznakaCvora;
public:
    MatricaGraf(int broj) : matrica(broj, std::vector<std::tuple<bool, float, Tip>>(broj, std::make_tuple(false, 0.0f, Tip{}))), oznakaCvora(broj) {
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
    void dodajGranu(int polazni, int dolazni, float tezina) override {
        matrica.at(polazni).at(dolazni) = std::make_tuple(true, tezina, Tip{});
    }
    void obrisiGranu(int polazni, int dolazni) override {
        // samo oznacima da nije povezana grana
        std::get<0>(matrica.at(polazni).at(dolazni)) = false;
    }
    void postaviTezinuGrane(int polazni, int dolazni, float tezina) override {
        std::get<1>(matrica.at(polazni).at(dolazni)) = tezina;
    }

    float dajTezinuGrane(int polazni, int krajnji) const override {
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

using namespace std;

int main() {
 UsmjereniGraf<bool> *g = new MatricaGraf<bool>(6);
    g->dodajGranu(0, 1, 2.5);
    g->dodajGranu(1, 0, 1.2);
    g->dodajGranu(1, 2, 0.1);
    g->dodajGranu(0, 0, 3.14);
    for (GranaIterator<bool> iter = g->dajGranePocetak();
         iter != g->dajGraneKraj(); ++iter)
      cout << "(" << (*iter).dajPolazniCvor().dajRedniBroj() << ","
           << (*iter).dajDolazniCvor().dajRedniBroj() << ") -> "
           << (*iter).dajTezinu() << "; ";
  delete g;
    return 0;
}
