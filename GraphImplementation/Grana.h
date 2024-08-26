#ifndef GRANA_H
#define GRANA_H

#include "GranaIterator.h"

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

#endif