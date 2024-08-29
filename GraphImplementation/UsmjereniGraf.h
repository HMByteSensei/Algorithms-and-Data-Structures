#ifndef USMJERENIGRAF_H
#define USMJERENIGRAF_H

#include "GranaIterator.h"

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

#endif