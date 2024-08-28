#ifndef MATRICAGRAF_H
#define MATRICAGRAF_H

#include "GranaIterator.h"

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

#endif