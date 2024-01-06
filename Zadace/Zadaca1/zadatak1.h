#ifndef ZADATAK1_H
#define ZADATAK1_H

template <typename Tip> 
class Lista {
public:
  Lista() {}
  virtual ~Lista() {}

  virtual int brojElemenata() const = 0;
  /*
      ako je lista prazna, metode trenutni, prethodni, sljedeci, pocetak, kraj i
     obrisi trebaju baciti izuzetak;
  */
  virtual Tip &trenutni() = 0;
  virtual Tip trenutni() const = 0;

  virtual bool prethodni() = 0;
  virtual bool sljedeci() = 0;
  virtual void pocetak() = 0;
  virtual void kraj() = 0;
  virtual void obrisi() = 0;
  //----------------------------
  virtual void dodajIspred(const Tip &el) = 0;
  virtual void dodajIza(const Tip &el) = 0;

  // predavanje 11a strana 3
  virtual Tip &operator[](int i) = 0; // za poziv nad nekonstantnim objektima
  virtual Tip operator[](int i) const = 0; // za poziv nad konstantnim objektima
};

#endif