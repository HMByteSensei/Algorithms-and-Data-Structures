#ifndef TEST_H
#define TEST_H

#include "zadatak1.h"
#include <iostream>
#include <iomanip>

// -----------------------------TEST---------------------------------
template <typename Tip>
void generisanjeListe(Lista<Tip> &l) {
    if(l.brojElemenata() != 0) { return; }
    for(int i=0; i<=5; i++) {
        l.dodajIspred(i);
    }
}

template <typename Tip>
void prikaziListu(Lista<Tip> &l) {
    // std::cout << " i: " << i << "  --->  " << l.trenutni() << " ";
    l.pocetak();
    for(int i=0; i<l.brojElemenata(); i++) {
        std::cout << " " << l.trenutni() << " ";
        l.sljedeci();
    }
    std::cout << "\nBROJ ELEMENATA: " <<l.brojElemenata() <<"\n";
}

template <typename TIP>
bool testBrojElemenata(Lista<TIP> &l) {
    generisanjeListe(l);
    if(l.brojElemenata() != 6) {
        std::cout << "\n\tNeispravan broj elemenata: " << l.brojElemenata() << ", a treba biti 6!";
        return false;
    }
    std::cout << "\nIspravan broj elemenata: " << l.brojElemenata() << " i treba biti 6!";
    return true;
}
  
/*
 *  ako je lista prazna, metode trenutni, prethodni, sljedeci, pocetak, kraj i
 *  obrisi trebaju baciti izuzetak;
*/

// za testiranje da li dolazi do bacanja izuzetka
template <typename Tip>
bool testIzuzetka(int n, Lista<Tip> &temp) {
    // Lista<Tip> *temp = nullptr;
    try {
        switch(n) {
            case 0:
                temp.trenutni();
                break;
            case 1:
                temp.prethodni();
                break;
            case 2:
                temp.sljedeci();
                break;
            case 3:
                temp.pocetak();
                break;
            case 4:
                temp.kraj();
                break;
            default:
                temp.obrisi();
        }
    } catch(std::range_error e) {
        e.what();
        std::cout << "Doslo je do bacanja izuzetka!\n";
        return true;
    }
    std::cout << "Nije doslo do bacanja izuzetka!\n";
    return false;
}

template <typename Tip>
void testTrenutni(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje trenutni() samo za nekonstantne liste: \n" << std::setw(10) << std::setfill('-') << "\n";
    testIzuzetka<Tip>(0, k);
    generisanjeListe(l);
    std::cout << "Trenutni element je: " << l.trenutni();

    std::cout << "\nTestiranje izmjene elementa:\n";
    l.trenutni() = 10;
    std::cout << "\tDa li je trenutni element 10: " << ((l.trenutni() == 10) ? "Jeste" : "Nije");

    std::cout << "\nElementi liste: ";
    prikaziListu(l);
    std::cout << "\nTrenutni element je: " << l.trenutni();
    std::cout << "\n" << std::setw(10) << std::setfill('-') << "\n";
}

template <typename Tip>
void testPrethodni(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje prethodni(): \n" << std::setw(10) << std::setfill('-') << "\n";
    testIzuzetka<Tip>(1,k);
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    
    std::cout << "Trenutni element je: " << l.trenutni();
    l.prethodni();
    std::cout << "\nNakon poziva prethodni(), trenutni element je: " << l.trenutni();

    std::cout << "\nZa listu od elemenata {0}: ";
    k.dodajIza(0);
    std::cout << "\n\tPravljenje nove liste i dodavanje elementa 0 uz metodu dodajIza(). Print liste: " << k.trenutni();
    std::cout << ( (k.trenutni() == 0) ? "OK" : "Trenutni od k ne daje 0" );
    // Brisanje elementa da bi lista k ostala prazna
    k.obrisi();
    std::cout << "\n" << std::setw(10) << std::setfill('-') << "\n";    
}

template <typename Tip>
void testSljedeci(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje sljedeci(): \n" << std::setw(10) << std::setfill('-') << "\n";
    testIzuzetka<Tip>(2, k);
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    
    std::cout << "Trenutni element je: " << l.trenutni();
    l.sljedeci();
    std::cout << "\nNakon poziva sljedeci(), trenutni element je: " << l.trenutni();

    std::cout << "\nZa listu od elemenata {0}: ";
    k.dodajIza(0);
    std::cout << "\n\tPravljenje nove liste i dodavanje elementa 0 uz metodu dodajIza(). Print liste: " << k.trenutni();
    std::cout << ( (k.trenutni() == 0) ? "OK" : "Trenutni od k ne daje 0" );
    // Brisanje elementa da lista k bude opet prazna
    k.obrisi();
    std::cout << "\n" << std::setw(10) << std::setfill('-') << "\n";   
}

template <typename Tip>
void testPocetak(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje pocetak(): \n" << std::setw(10) << std::setfill('-') << "\n";
    testIzuzetka<Tip>(3, k);
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    
    std::cout << "Trenutni element je: " << l.trenutni();
    l.pocetak();
    std::cout << "\nNakon poziva pocetak(), trenutni element je: " << l.trenutni();
    std::cout << "\n" << std::setw(10) << std::setfill('-') << "\n"; 
}

template <typename Tip>
void testKraj(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje kraj(): \n" << std::setw(10) << std::setfill('-') << "\n";
    testIzuzetka<Tip>(4, k);
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    // prikaziListu() stavlja da trenutni bude kraj tj trenutni ce pokazivati na zadnji element

    l.kraj();
    std::cout << "\nNakon poziva kraj(), trenutni element je: " << l.trenutni();
    std::cout << "\n" << std::setw(10) << std::setfill('-') << "\n"; 
}

template <typename Tip>
void testObrisi(Lista<Tip> &l, Lista<Tip> &k) {
    std::cout << "\nTestiranje obrisi(): \n" << std::setw(10) << std::setfill('/') << "\n";
    testIzuzetka<Tip>(5, k);
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    
    std::cout << "Trenutni element je: " << l.trenutni();
    l.obrisi();
    std::cout << "\nNakon poziva obrisi(), trenutni element je: " << l.trenutni();
    std::cout << "\nElementi liste(treba da se obrisao element): ";
    prikaziListu(l);
    std::cout << "\nSada pozivamo dva puta metodu prethodni i onda brisemo element:\n";
    l.prethodni();
    l.prethodni();
    std::cout << "\nTrenutni element je: " << l.trenutni() << "\n";
    l.obrisi();
    std::cout << "\nNakon brisanja trenutni element je: " << l.trenutni() << ", a prikaz liste:\n";
    prikaziListu(l);
    std::cout << "\n" << std::setw(10) << std::setfill('/') << "\n";
}
//----------------------------

template <typename Tip>
void testDodajIspred(Lista<Tip> &l) {
    std::cout << "\nTestiranje dodajIspred(): \n" << std::setw(10) << std::setfill('*') << "\n";
    // std::cout << "Ako je lista prazna i dodamo element sa dodajIspred(5) trenutni element je: ";
    // Lista<Tip> *nova;
    // nova->dodajIspred(5);
    // std::cout << nova->trenutni();
    std::cout << "\nGeneriranje nove liste: \n";
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    std::cout << "\nDodali element 5 s dodajIspred(), trenutni element nakon metode je: ";
    l.dodajIspred(5);
    std::cout << l.trenutni() << "\n";
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    std::cout << "\n" << std::setw(10) << std::setfill('*') << "\n";
}

template <typename Tip>
void testDodajIza(Lista<Tip> &l) {
    std::cout << "\nTestiranje dodajIza(): \n" << std::setw(10) << std::setfill('*') << "\n";
    // std::cout << "Ako je lista prazna i dodamo element sa dodajIza(5) trenutni element je: ";
    // Lista<Tip> *nova;
    // nova->dodajIza(5);
    // std::cout << nova->trenutni();
    std::cout << "\nGeneriranje nove liste:\n";
    generisanjeListe(l);
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    std::cout << "\nDodali element 7 s dodajIza(), trenutni element nakon metode je: ";
    l.dodajIza(7);
    std::cout << l.trenutni() << "\n";
    std::cout << "Elementi liste: ";
    prikaziListu(l);
    std::cout << "\n" << std::setw(10) << std::setfill('*') << "\n";
}

// predavanje 11a strana 3
template <typename Tip>
void testOperatoraUglasteZagrade(Lista<Tip> &l) {
    std::cout << "\nTestiranje operator[](): \n" << std::setw(10) << std::setfill('#') << "\n";
    generisanjeListe(l);
    prikaziListu(l);
    try {
        l[-1];
    } catch(std::range_error e) {
        std::cout << "\nIndeks je -1: " << e.what();
    }
    try {
        l[l.brojElemenata() + 1];
    } catch(std::range_error e) {
        std::cout << "\nIndeks je brElemenata + 1: " << e.what() << "\n";
    }
    std::cout << "Elementi niza unazad:\n";
    for(int i=l.brojElemenata() - 1; i >= 0; i--) {
        std::cout << " " << l[i] << "\t";
    }
    std::cout << "\nElement s indeksom 3(dakle 4 element) je " << l[3];
    l[3] = 9;
    std::cout << ", a nakon izmjene da li je 9? " << l[3] << "\n";
    std::cout << "Elementi niza naprijed:\n";
    for(int i=0; i < l.brojElemenata(); i++) {
        std::cout << " " << l[i] << "\t";
    }
    std::cout << "\n" << std::setw(10) << std::setfill('#') << "\n";
}

template <typename Tip>
void mainTest(Lista<Tip> &l, Lista<Tip> &k) {
    /*
        generirajPraznuListu(l) prvo trebamo pozvati da testiramo 
        implementaciju i nad praznom listom, a izmedju ostalog i operator dodjele
    */
    // generirajPraznuListu(l);
    testBrojElemenata(l);
    testTrenutni(l, k);
    testPrethodni(l, k);
    testSljedeci(l, k);
    testPocetak(l, k);
    testKraj(l, k);
    testObrisi(l, k);
    testDodajIspred(l);
    testDodajIza(l);
    testOperatoraUglasteZagrade(l);
    std::cout << "\n\tKRAJ TESTIRANJA";
}
// -----------------------------KRAJ TEST-a---------------------------------

#endif