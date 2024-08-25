#ifndef CVOR_H
#define CVOR_H

template <typename Tip>
class Cvor {
private:
    int redni_broj;
    UsmjereniGraf<Tip> *ug;
public:
    Cvor(UsmjereniGraf<Tip> *graf, int redniBrCvora) : ug(graf), redni_broj(redniBrCvora) {};
};

#endif
