#include iostream
#include stdexcept
#include vector
#include tuple
#include queue
 ne dopusta se da dva cvora imaju vise od jedne grane
template typename Tip
class Grana;

template typename Tip
class Cvor;

template typename Tip
class UsmjereniGraf;

template typename TipOznake
class GranaIterator {
    UsmjereniGrafTipOznake ug;
    int pocetna_poz, krajnja_poz;
    int brojac_inkrementacija;
    GranaIterator() {}
public
    GranaIterator(UsmjereniGrafTipOznake graf, int poc, int kraj) {
        ug = graf;
        pocetna_poz = poc;
        krajnja_poz = kraj;
        brojac_inkrementacija = 0;
    }
    GranaTipOznake operator() {return ug-dajGranu(pocetna_poz, krajnja_poz); }
    bool operator==(const GranaIterator &iter) { return &iter == this; }
    bool operator!=(const GranaIterator &iter) { return &iter != this; }
    GranaIterator& operator++() {
            do {
                if(krajnja_poz = ug-dajBrojCvorova()-1) {
                    pocetna_poz++;
                    krajnja_poz = 0;
                } else krajnja_poz++;
                
                if(pocetna_poz = ug-dajBrojCvorova()) {
                    break;
                }
            } while(ug-postojiGrana(pocetna_poz, krajnja_poz));
         if((++brojac_inkrementacija) = ug-dajBroj);

        return this;
    }
    GranaIterator operator++(int) {
        GranaIteratorTipOznake kopija(this);
        this-operator++();
        return kopija;
    }
};

template typename Tip
class UsmjereniGraf {
private
    int brojCvorova;
    mutable bool pocetak = false;
public
    UsmjereniGrafTip() {};
    UsmjereniGraf(int brojCvorova) { this-brojCvorova = brojCvorova; }
    virtual int dajBrojCvorova() const = 0;
    
    virtual ~UsmjereniGraf(){};
    virtual void postaviBrojCvorova(int br) = 0;
    virtual void dodajGranu(int polazni, int dolazni, float tezina) = 0;
    virtual void obrisiGranu(int polazni, int dolazni) = 0;
    virtual void postaviTezinuGrane(int polazni, int dolazni, float tezina)  = 0;
    
    virtual float dajTezinuGrane(int polazni, int krajnji) const = 0;
    virtual bool postojiGrana(int pocetni, int krajnji) const = 0;

     vraca true ako se uspjesno postavila oznaka
    virtual void postaviOznakuCvora(int pozicija_cvora, Tip oznaka) = 0;
    virtual void postaviOznakuGrane(int pocetni, int krajnji, Tip oznaka) = 0;
    
    virtual Tip dajOznakuCvora(int pozicija_cvora) = 0;
    virtual Tip dajOznakuGrane(int pocetni, int krajnji) const = 0;

    virtual GranaTipdajGranu(int pocetniCvor, int krajnjiCvor) = 0;
    virtual CvorTip dajCvor(int pozicija) = 0;

    virtual GranaIteratorTip dajGranePocetak() {
        if(!pocetak) {
            pocetak = true;
            return ++GranaIteratorTip(this, 0, this-dajBrojCvorova());
        }
        return ++GranaIteratorTip(this, 0, -1);
    } 
    virtual GranaIteratorTip dajGraneKraj() {
        return GranaIteratorTip(this, this-dajBrojCvorova(), 0);
    }
};


template typename Tip
class Grana {
    UsmjereniGrafTip ug;
    int pocetnaPozicija, krajnjaPozicija;
public 
    Grana(UsmjereniGrafTip graf, int poc, int kraj)  ug(graf), pocetnaPozicija(poc), krajnjaPozicija(kraj) {}

    float dajTezinu() const { return ug-dajTezinuGrane(pocetnaPozicija, krajnjaPozicija);}
    Tip dajOznaku() const {
        return ug-dajOznakuGrane(pocetnaPozicija, krajnjaPozicija);
    }
    void postaviTezinu(float tezina) {
        ug-postaviTezinuGrane(pocetnaPozicija, krajnjaPozicija);
    }
    void postaviOznaku(Tip oznaka) {
        ug-postaviOznakuGrane(pocetnaPozicija, krajnjaPozicija, oznaka);
    }
    CvorTip dajPolazniCvor() const {return ug-dajCvor(pocetnaPozicija);} 
    CvorTip dajDolazniCvor() const {
        return ug-dajCvor(krajnjaPozicija);
    }
};

template typename Tip
class Cvor {
private
    int redni_broj;
    UsmjereniGrafTip ug;
public
    Cvor(UsmjereniGrafTip graf, int redniBrCvora)  ug(graf), redni_broj(redniBrCvora) {};
    
    Tip dajOznaku() const {return ug-dajOznakuCvora(redni_broj);}
    void postaviOznaku(Tip oznaka) {
        ug-postaviOznakuCvora(redni_broj, oznaka);
    }
    int dajRedniBroj() const {return redni_broj;}
};

templatetypename Tip
class MatricaGraf  public UsmjereniGrafTip {
private
    int brojCvorova;
     bool = da li je povezano ili ne, float je tezina grane, Tip = oznaka 
    stdvectorstdvectorstdtuplebool, float, Tip matrica;
    stdvectorTip oznakaCvora;
public
    MatricaGraf(int broj)  matrica(broj, stdvectorstdtuplebool, float, Tip(broj, stdmake_tuple(false, 0.0f, Tip{}))), oznakaCvora(broj) {
        brojCvorova = broj;
    }
    MatricaGraf() {};
    ~MatricaGraf(){};
    int dajBrojCvorova() const override {
        return oznakaCvora.size();
    }
    void postaviBrojCvorova(int br) override {
        if(br  brojCvorova) {
            throw stddomain_error(Nije dozvoljeno da postavite manji broj cvorova od postojeceg);
        }
        matrica.resize(br);
        for(int i=brojCvorova; ibr; i++) {
            matrica.at(i).resize(br, stdmake_tuple(false, 0.0f, Tip{}));
        }
        brojCvorova = br;
    }
    void dodajGranu(int polazni, int dolazni, float tezina) override {
        matrica.at(polazni).at(dolazni) = stdmake_tuple(true, tezina, Tip{});
    }
    void obrisiGranu(int polazni, int dolazni) override {
         samo oznacima da nije povezana grana
        stdget0(matrica.at(polazni).at(dolazni)) = false;
    }
    void postaviTezinuGrane(int polazni, int dolazni, float tezina) override {
        stdget1(matrica.at(polazni).at(dolazni)) = tezina;
    }

    float dajTezinuGrane(int polazni, int krajnji) const override {
        return stdget1(matrica.at(polazni).at(krajnji));
    }
    bool postojiGrana(int pocetni, int krajnji) const override {
        return stdget0(matrica.at(pocetni).at(krajnji));
    }

 vraca true ako se uspjesno postavila oznaka
    void postaviOznakuCvora(int pozicija_cvora, Tip oznaka) override {
        oznakaCvora.at(pozicija_cvora) = oznaka;
    }
    void postaviOznakuGrane(int pocetni, int krajnji, Tip oznaka) override {
        stdget2(matrica.at(pocetni).at(krajnji)) = oznaka;
    }

    Tip dajOznakuCvora(int pozicija_cvora) override {
        return oznakaCvora.at(pozicija_cvora);
    }
    Tip dajOznakuGrane(int pocetni, int krajnji) const override {
        return stdget2(matrica.at(pocetni).at(krajnji));
    }

    GranaTipdajGranu(int pocetniCvor, int krajnjiCvor) override {
        return GranaTip(this, pocetniCvor, krajnjiCvor);
    }
    CvorTip dajCvor(int pozicija) override {
        if(pozicija  0  pozicija = dajBrojCvorova()) {
            throw stdrange_error(Pozicija izvan opsega);
        }
        return CvorTip(this, pozicija);
    }
};

 BFS
templatetypename Tip
void recursiveBFS(UsmjereniGrafTip ug, stdvectorCvorTip &obilazak, stdqueueCvorTip &q);

template typename Tip
void bfs(UsmjereniGrafTip ug, stdvectorCvorTip &obilazak, CvorTip cvor) {
    cvor.postaviOznaku(1);
    obilazak.push_back(cvor);
    stdqueueCvorTip red;
    red.push(cvor);
    recursiveBFS(ug, obilazak, red);
}

templatetypename Tip
void recursiveBFS(UsmjereniGrafTip ug, stdvectorCvorTip &obilazak, stdqueueCvorTip &q) {
    if(q.empty()) {
        return;
    }
    CvorTip c = q.front();
    q.pop();
    obradiSusjedni(ug, obilazak, q, c);

    recursiveBFS(ug, obilazak, q);
}

templatetypename Tip
void obradiSusjedni(UsmjereniGrafTip ug, stdvectorCvorTip &obilazak, stdqueueCvorTip &q, CvorTip c) {
    GranaIteratorTip grana = ug-dajGranePocetak();

    for(auto pom = grana; pom != ug-dajGraneKraj(); pom++) {
        auto start = (pom).dajPolazniCvor();
        auto end = (pom).dajDolazniCvor();
    
        if(end.dajOznaku() != 1 && start.dajRedniBroj() == c.dajRedniBroj()) {
            end.postaviOznaku(1);
            obilazak.push_back(end);
            q.push(end);
        }
    }
}

DFS
templatetypename Tip
void dfs(UsmjereniGrafTip ug, stdvectorCvorTip &obilazak, CvorTip c) {
    c.postaviOznaku(1);
    obilazak.push_back(c);
    for(GranaIteratorTip iter = ug-dajGranePocetak(); iter != ug-dajGraneKraj(); iter++) {
        if((iter).dajPolazniCvor().dajRedniBroj() == c.dajRedniBroj() && (iter).dajDolazniCvor().dajOznaku() != 1) {
            dfs(ug, obilazak, (iter).dajDolazniCvor());
        }
    }
}

using namespace std;

int main() {
 UsmjereniGrafbool g = new MatricaGrafbool(6);
    g-dodajGranu(0, 1, 2.5);
    g-dodajGranu(1, 0, 1.2);
    g-dodajGranu(1, 2, 0.1);
    g-dodajGranu(0, 0, 3.14);
    int brojac = 0;
    for (GranaIteratorbool iter = g-dajGranePocetak();
         iter != g-dajGraneKraj(); ++iter) {
                cout  (  (iter).dajPolazniCvor().dajRedniBroj()  ,
                     (iter).dajDolazniCvor().dajRedniBroj()  ) - 
                     (iter).dajTezinu()  ; ;

         }
  delete g;
    return 0;
}