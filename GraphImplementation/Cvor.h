#ifndef CVOR_H
#define CVOR_H

#include "GranaIterator.h"

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

#endif