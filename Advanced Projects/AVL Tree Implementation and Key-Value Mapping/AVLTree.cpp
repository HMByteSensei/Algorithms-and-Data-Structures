#include <iostream>
#include <random>
#include <ctime>

/*
 AVL STABLO koje pravi stablo po kljucevima a ne po 
 njihovim pridruzenim elementima/vrijednostima
*/

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
class AVLStabloMapa : public Mapa<Kljuc, Vrijednost> {
private:
    struct Cvor {
        Kljuc kljuc;
        Vrijednost element;
        Cvor *roditelj;
        Cvor *lijevoDijete;
        Cvor *desnoDijete;
        int balans;
    };
    Cvor *korijen;
    int velicina;
    void postOrderBrisanje(Cvor *trenutni) {
        if(trenutni == nullptr) { return; }
        postOrderBrisanje(trenutni->lijevoDijete);
        postOrderBrisanje(trenutni->desnoDijete);
        delete trenutni;
        velicina--;
    }
    void inOrderispis(Cvor *r) const {
        if(r == nullptr) { return; }
        inOrderispis(r->lijevoDijete);
        if(r->roditelj!= nullptr) {
            std::cout << "(" << r->roditelj->element << ", "<< r->element << ", " << r->balans << ") ";
        } else {
            std::cout << "(" << r->element << ", " << r->balans << ") ";
        }
        inOrderispis(r->desnoDijete);
    }
    void preOrderKopiraj(const Cvor *kopija, Cvor *&ovaj) {
        if(kopija != nullptr) {
            //Cvor *novi 
            ovaj = new Cvor{kopija->kljuc, kopija->element, kopija->roditelj, 
                kopija->lijevoDijete, kopija->desnoDijete};
            preOrderKopiraj(kopija->lijevoDijete, ovaj->lijevoDijete);
            preOrderKopiraj(kopija->desnoDijete, ovaj->desnoDijete);
        }
    }
    // parametari su roditelj od kojeg se starta i da li je njegovo dijete desno ili ne
    // azurira balans od startRoditelj cvora pa do korijena uklj. i korijen
    void azurirajBalans(Cvor *startRoditelj, bool daLiJeDesnoDijete);
    // azuriranje nakon rotacije se obavlja suprotno nego azuriranje gdje je potrebna rot
    void azurirajBalansNakonRotacije(Cvor *startRoditelj, bool daLiJeDesnoDijete);
    // kriticniCvor je ustvari roditelj oko kojeg rotiramo
    // desno dijete postaje roditelj, a roditelj postaje lijevo dijete
    void rotirajLijevo(Cvor *kriticniCvor);
    // lijevo dijete postaje roditelj, a roditelj postaje desno dijete
    void rotirajDesno(Cvor *kriticniCvor);
    // desnaGrana vraca da li se nalazimo u desnoj grani tj da li je trenutni cvor s desne str roditelja
    bool desnaGrana(Cvor *trenutni) const;
    Kljuc nadjiMax(Cvor *korijen) {
        Kljuc max{};
        while(korijen!=nullptr) {
            max = korijen->kljuc;
            korijen = korijen->desnoDijete;
        }
        return max;
    }
    void preorderIspis(Cvor *kopija, const Kljuc &max) {
        if(kopija != nullptr) {
            std::cout << kopija->kljuc;
            if(kopija->kljuc != max) {
                std::cout << ",";
            } 
            preorderIspis(kopija->lijevoDijete, max);
            preorderIspis(kopija->desnoDijete, max);
        }
    }
public:
    AVLStabloMapa() : korijen(nullptr), velicina(0) {};
    ~AVLStabloMapa() { obrisi(); }
    AVLStabloMapa(AVLStabloMapa &k);
    AVLStabloMapa &operator=(const AVLStabloMapa &b);
    Vrijednost &operator[](const Kljuc &k) override;
    Vrijednost operator[](const Kljuc &k) const override;
    int brojElemenata() const override { return velicina; }
    void obrisi() override;
    void obrisi(const Kljuc &kljuc) override;
    void ispisi() const;
    // ispisuje kljuceve stabla u preorder redoslijedu
    void preorder() {
        preorderIspis(korijen, nadjiMax(korijen));
    }
};

template <typename Kljuc, typename Vrijednost>
void AVLStabloMapa<Kljuc, Vrijednost>::ispisi() const {
    std::cout << "\nIspis oblika (element, balans): \n";
    inOrderispis(korijen);
}

template <typename Kljuc, typename Vrijednost>
AVLStabloMapa<Kljuc, Vrijednost>::AVLStabloMapa(AVLStabloMapa<Kljuc, Vrijednost> &k) {
    korijen = nullptr;
    preOrderKopiraj(k.korijen, korijen);
    this->velicina = k.brojElemenata();
}

template <typename Kljuc, typename Vrijednost>
AVLStabloMapa<Kljuc, Vrijednost> &AVLStabloMapa<Kljuc, Vrijednost>::operator=(const AVLStabloMapa &k) {
    if(this == &k) {
        return *this;
    }
    obrisi();
    korijen = nullptr;
    preOrderKopiraj(k.korijen, korijen);
    this->velicina = k.velicina;
    return *this;
}

template <typename Kljuc, typename Vrijednost>
void AVLStabloMapa<Kljuc, Vrijednost>::azurirajBalansNakonRotacije(Cvor *startRoditelj, bool daLiJeDesnoDijete) {
    while(startRoditelj != korijen) {
        // ako je desnoDijete u pitanju umanjujemo balans roditelja
        // a inace povecavamo balans roditelja
        if(daLiJeDesnoDijete) {
            startRoditelj->balans += 1;
            
        } else {
            startRoditelj->balans -= 1;
        }
        if(startRoditelj->kljuc < startRoditelj->roditelj->kljuc) {
            daLiJeDesnoDijete = false;
        } else {
            daLiJeDesnoDijete = true;
        }
        startRoditelj = startRoditelj->roditelj;
    }
    // azuriramo i korijenski cvor
    if(daLiJeDesnoDijete) {
        startRoditelj->balans += 1;
    } else {
        startRoditelj->balans -= 1;
    }
}

template <typename Kljuc, typename Vrijednost>
void AVLStabloMapa<Kljuc, Vrijednost>::rotirajLijevo(Cvor *kriticniCvor) {
    // desno dijete postaje roditelj, a roditelj postaje lijevo dijete
    // situacija npr 20 <-> 23 <-> 25 gdje je stablo desno nagnuto
    // i gdje je korijen 20 pa sredivanje pokazivaca u nastavku 
    Cvor *noviRoditelj = kriticniCvor->desnoDijete;
    kriticniCvor->desnoDijete = noviRoditelj->lijevoDijete;
    if(noviRoditelj->lijevoDijete != nullptr) {
        noviRoditelj->lijevoDijete->roditelj = kriticniCvor;
    }
    noviRoditelj->lijevoDijete = kriticniCvor;
    if(kriticniCvor == korijen) {
        korijen = noviRoditelj;
        noviRoditelj->roditelj = nullptr;
    } else {
        noviRoditelj->roditelj = kriticniCvor->roditelj;
        if(desnaGrana(kriticniCvor)) {
            noviRoditelj->roditelj->desnoDijete = noviRoditelj;
        } else {
            noviRoditelj->roditelj->lijevoDijete = noviRoditelj;
        }
    }
    kriticniCvor->roditelj = noviRoditelj;
    //int noviBalans = kriticniCvor->balans + 1 - noviRoditelj->balans;
    kriticniCvor->balans = 0;
    //noviBalans = noviRoditelj->balans + 1;
    noviRoditelj->balans = 0;
}

template <typename Kljuc, typename Vrijednost>
void AVLStabloMapa<Kljuc, Vrijednost>::rotirajDesno(Cvor *kriticniCvor) {
    // lijevo dijete postaje novi roditelj, a roditelj(kriticni cvor) postaje desno dijete
    Cvor *noviRoditelj = kriticniCvor->lijevoDijete;
    kriticniCvor->lijevoDijete = noviRoditelj->desnoDijete;
    // nullptr nije Cvor pa ne moze imati roditelja
    if(noviRoditelj->desnoDijete != nullptr) {
        noviRoditelj->desnoDijete->roditelj = kriticniCvor;
    }
    noviRoditelj->desnoDijete = kriticniCvor;
    if(kriticniCvor == korijen) {
        korijen = noviRoditelj;
        noviRoditelj->roditelj = nullptr;
    } else {
        noviRoditelj->roditelj = kriticniCvor->roditelj;
        if(!desnaGrana(kriticniCvor)) {
            noviRoditelj->roditelj->lijevoDijete = noviRoditelj;
        } else {
            noviRoditelj->roditelj->desnoDijete = noviRoditelj;
        }
    }
    kriticniCvor->roditelj = noviRoditelj;
    // jer smo rotiraliDesno tj jedan cvor smo pomjerili iznad noviRoditelj, a drugi kriticni ispod
    //int noviBalans = kriticniCvor->balans - 1 + noviRoditelj->balans;
    kriticniCvor->balans = 0;
    //noviBalans = noviRoditelj->balans - 1;
    noviRoditelj->balans = 0;
}

template <typename Kljuc, typename Vrijednost>
bool AVLStabloMapa<Kljuc, Vrijednost>::desnaGrana(Cvor *trenutni) const {
    if(trenutni->kljuc > trenutni->roditelj->kljuc) {
        return true;
    }
    return false;
}

template <typename Kljuc, typename Vrijednost>
void AVLStabloMapa<Kljuc, Vrijednost>::azurirajBalans(Cvor *startRoditelj, bool daLiJeDesnoDijete) {
    while(startRoditelj != korijen) {
        // ako je desnoDijete u pitanju umanjujemo balans roditelja
        // a inace povecavamo balans roditelja
        if(daLiJeDesnoDijete) {
            startRoditelj->balans -= 1;
            // negativno => nagnuto u desnu stranu, poz => nagnuto u lijevu stranu
            if(startRoditelj->balans < -1) {
                // ispitivanje kako je nagnuto dijete od kriticnog cvora
                if(startRoditelj->desnoDijete->balans < 0) {
                    rotirajLijevo(startRoditelj);
                } else {
                    // cuvamo balans za cvor dva nivoa ispod kriticnog npr za A(-2)->B(1)->C(-1)
                    // cuvamo balans za cvor C 
                    int balans = startRoditelj->desnoDijete->lijevoDijete->balans;
                    rotirajDesno(startRoditelj->desnoDijete);
                    rotirajLijevo(startRoditelj);
                    // ovo se dogadja kada je balans kriticnog cvora suprotan od balansa njegovog djeteta
                    // npr. A(-2)->B(1)->C(-1) gdje je kriticni cvor A, i prikaz je dat u formatu Cvor(balans)
                    // Ovo je jedina situacija koja se moze pojaviti zbog koje je potrebno prvo rot u desno, 
                    // pa onda u lijevo a balans kriticnog cvora nakon promjene je abs(C) jer C moze biti -1 
                    // ili 0
                    startRoditelj->balans = std::abs(balans);
                }
                azurirajBalansNakonRotacije(startRoditelj->roditelj, desnaGrana(startRoditelj));
            }
        } else {
            startRoditelj->balans += 1;
            // negativno => nagnuto u desnu stranu, poz => nagnuto u lijevu stranu
            if(startRoditelj->balans > 1) {
                // ispitivanje kako je nagnuto dijete od kriticnog cvora
                if(startRoditelj->lijevoDijete->balans < 0) {
                    // analogno kao i gore
                    int balans = startRoditelj->lijevoDijete->desnoDijete->balans;
                    rotirajLijevo(startRoditelj->lijevoDijete);
                    rotirajDesno(startRoditelj);
                    // analogno kao gore samo sto je ovdje balans kriticnog cvora na kraju -1
                    startRoditelj->balans = std::abs(balans);
                } else {
                    rotirajDesno(startRoditelj);
                }
                azurirajBalansNakonRotacije(startRoditelj->roditelj, desnaGrana(startRoditelj));
            }
        }
        if(startRoditelj->kljuc < startRoditelj->roditelj->kljuc) {
            daLiJeDesnoDijete = false;
        } else {
            daLiJeDesnoDijete = true;
        }
        startRoditelj = startRoditelj->roditelj;
    }
    // azuriramo i korijenski cvor
    if(daLiJeDesnoDijete) {
        startRoditelj->balans -= 1;
        // negativno => nagnuto u desnu stranu, poz => nagnuto u lijevu stranu
        if(startRoditelj->balans < -1) {
            // ispitivanje kako je nagnuto dijete od kriticnog cvora
            if(startRoditelj->desnoDijete->balans < 0) {
                rotirajLijevo(startRoditelj);
            } else {
                int balans = startRoditelj->desnoDijete->lijevoDijete->balans;
                rotirajDesno(startRoditelj->desnoDijete);
                rotirajLijevo(startRoditelj);
                startRoditelj->balans = std::abs(balans);
                // azurirajBalansBezRotacije(startRoditelj->roditelj, desnaGrana(startRoditelj));
            }
        }
    } else {
        startRoditelj->balans += 1;
        // negativno => nagnuto u desnu stranu, poz => nagnuto u lijevu stranu
        if(startRoditelj->balans > 1) {
            // ispitivanje kako je nagnuto dijete od kriticnog cvora
            if(startRoditelj->lijevoDijete->balans < 0) {
                int balans = startRoditelj->lijevoDijete->desnoDijete->balans;
                rotirajLijevo(startRoditelj->lijevoDijete);
                rotirajDesno(startRoditelj);
                startRoditelj->balans = std::abs(balans);
            } else {
                rotirajDesno(startRoditelj);
            }
        }
    }
}


template <typename Kljuc, typename Vrijednost>
Vrijednost &AVLStabloMapa<Kljuc, Vrijednost>::operator[](const Kljuc &k) {
    Cvor *trenutni = korijen;
    Cvor *roditelj = nullptr;
    while(trenutni != nullptr) {
        if(trenutni->kljuc == k) {
            return trenutni->element;
        } else if(trenutni->kljuc < k) {
            roditelj = trenutni;
            trenutni = trenutni->desnoDijete;
        } else {
            roditelj = trenutni;
            trenutni = trenutni->lijevoDijete;
        }
    }
    // ako se do sada ne nalazi cvor u stablu sada ga dodajemo i njegov balans je 0
    Cvor *temp = new Cvor{k, Vrijednost(), roditelj, nullptr, nullptr, 0};
    if(korijen == nullptr) {
        korijen = temp;
    } else if(roditelj->kljuc < k) {
        roditelj->desnoDijete = temp;
        azurirajBalans(roditelj, true);
    } else if(roditelj->kljuc > k) {
        roditelj->lijevoDijete = temp;
        azurirajBalans(roditelj, false);
    }
    velicina++;
    return temp->element;
}

template <typename Kljuc, typename Vrijednost>
Vrijednost AVLStabloMapa<Kljuc, Vrijednost>::operator[](const Kljuc &k) const {
    Cvor *trenutni = korijen;
    while(trenutni != nullptr) {
        if(trenutni->kljuc == k) {
            return trenutni->element;
        } else if(trenutni->kljuc < k) {
            trenutni = trenutni->desnoDijete;
        } else {
            trenutni = trenutni->lijevoDijete;
        }
    }
    return Vrijednost();
}

template <typename Kljuc, typename Vrijednost>
void AVLStabloMapa<Kljuc, Vrijednost>::obrisi() {
    postOrderBrisanje(korijen);
    korijen = nullptr;
}

template <typename Kljuc, typename Vrijednost>
void AVLStabloMapa<Kljuc, Vrijednost>::obrisi(const Kljuc &kljuc) {
    Cvor *p = korijen;
    // p je cvor kojeg treba obrisati
    Cvor *roditeljOdP = nullptr;
    while(p != nullptr && kljuc != p->kljuc) {
        roditeljOdP = p;
        if(kljuc < p->kljuc) {
            p = p->lijevoDijete;
        } else {
            p = p->desnoDijete;
        }
    }
    // ako trazeni cvor ne postoji
    if(p == nullptr) {
        return;
    }
    // ako cvor ima samo jedno dijete tada m treba da pokazuje na to dijete
    Cvor *m;
    // pm predstavlja roditelj od m
    Cvor *pm = nullptr;
    
    bool mJeDesno{};
    // ako cvor koji se brise nema lijevo dijete
    if(p->lijevoDijete == nullptr) {
        m = p->desnoDijete;
        mJeDesno = true;
    } else {
        // ako cvor koji se brise nema desno dijete
        if(p->desnoDijete == nullptr) {
            m = p->lijevoDijete;
            mJeDesno = false;
        } else {
            // ako cvor koji se brise ima i desno i lijevo dijete
            m = p->lijevoDijete;
            mJeDesno = false;
            pm = p;
            Cvor *tmp = m->desnoDijete;
            // idemo u lijevo podstablo i pronalazimo najdesniji cvor i na njega
            // stavimo da pokazuje m
            // a pm pokazuje na roditelja tog cvora
            while(tmp != nullptr) {
                pm = m;
                m = tmp;
                tmp = m->desnoDijete;
                mJeDesno = true;
            }
            // ako roditelj od m tj pm nije p tj cvor koji se brise
            if(pm != p) {
                // pm preuzima lijevo dijete od m
                pm->desnoDijete = m->lijevoDijete;
                if(pm->desnoDijete != nullptr)
                    pm->desnoDijete->roditelj = pm;
                // lijevo dijete od m postaje ono sto je lijevo dijete od p
                m->lijevoDijete = p->lijevoDijete;
                if(m->lijevoDijete != nullptr) 
                    m->lijevoDijete->roditelj = m;
            } else {
                pm = m;
                // m->balans = p->balans;
            }
            // desno dijete od m postaje ono sto je desno dijete od p
            m->desnoDijete = p->desnoDijete;
            if (m->desnoDijete != nullptr) {
                m->desnoDijete->roditelj = m;
            }
            m->roditelj = p->roditelj;
            p->roditelj->lijevoDijete = m;
        }
    }
    // ako se brise korijen
    if(roditeljOdP == nullptr) {
        korijen = p;
    } 
    else {
        if(p == roditeljOdP->lijevoDijete) {
            roditeljOdP->lijevoDijete = m;
        } else {
            roditeljOdP->desnoDijete = m;
        }
    }
    delete p;
    if(m == nullptr) {
        // ako ne brisemo list onda samo treba azurirati m
        if(roditeljOdP->lijevoDijete != nullptr || roditeljOdP->desnoDijete != nullptr) {
            while(roditeljOdP->kljuc != korijen->kljuc) {
                if(mJeDesno) {
                    roditeljOdP->balans += 1;
                } else {
                    roditeljOdP->balans -= 1;
                }
                mJeDesno = desnaGrana(roditeljOdP);
                roditeljOdP = roditeljOdP->roditelj;
            }
            if(mJeDesno) {
                korijen->balans += 1;
            } else {
                korijen->balans -= 1;
            }
        } else {
            if(mJeDesno) {
                roditeljOdP->balans += 1;
            } else {
                roditeljOdP->balans -= 1;
            }
        }
    } else {
        while(pm->kljuc != korijen->kljuc) {
            // if(pm == m) {
            //     mJeDesno = desnaGrana(pm);
            //     continue;
            // }
            if(mJeDesno) {
                pm->balans -= 1;
            } else {
                pm->balans += 1;
            }
            mJeDesno = desnaGrana(pm);
            pm = pm->roditelj;
        }
        if(mJeDesno) {
            roditeljOdP->balans += 1;
        } else {
            roditeljOdP->balans -= 1;
        }
    }
    roditeljOdP = nullptr;
    pm = nullptr;
    m = nullptr;
    velicina--;
}

int main() {
    AVLStabloMapa<int, int> stablo;
    
    stablo[30] = 30;
    stablo[20] = 20;
    stablo[40] = 40;
    stablo[25] = 25;
    stablo[23] = 23;
    stablo.preorder(); 
    stablo.obrisi();

    std::cout << "\n";
    stablo[1] = 1;
    stablo[2] = 2;
    stablo[3] = 3;
    stablo[4] = 4;
    stablo[5] = 5;
    stablo[6] = 6;
    stablo[7] = 7;
    stablo[8] = 8;
    stablo[9] = 9;
    stablo[10] = 10;
    stablo.preorder(); 
    stablo.obrisi();

    std::cout << "\nTest metode obrisi i mijenjanja elemenata u stablu: ";
    stablo[20] = 20;
    stablo[25] = 25;
    stablo[10] = 3;
    stablo.obrisi(10);
    stablo[30] = 30;
    stablo[20] = 20;
    stablo[40] = 40;
    stablo[25] = 25;
    stablo[23] = 23;
    stablo.preorder();
    stablo.obrisi();

    std::cout << "\nTest 3: ";
    stablo[30] = 30;
    stablo[20] = 20;
    stablo[40] = 40;
    stablo[37] = 37;
    stablo[35] = 35;
    stablo[1] = 1;
    stablo[2] = 2;
    stablo[3] = 3;
    stablo[4] = 4;
    stablo[5] = 5;
    stablo.preorder(); 

    // test 4 konstruktora kopije
    AVLStabloMapa<int, int> stablo2(stablo);
    std::cout << "\nStablo2:\n";
    stablo2.preorder();

    std::cout << "\n";
    stablo2.ispisi();

    stablo2.obrisi(40);
    stablo2.obrisi(3);
    std::cout << "\n";
    stablo2.ispisi();
    return 0;
}