#ifndef MAPA_H
#define MAPA_H

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

#endif