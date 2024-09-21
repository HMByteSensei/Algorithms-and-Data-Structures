#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int nadjiMax(std::vector<int> &a) {
    int max = a.at(0);
    for(int i=1; i<a.size(); i++) {
        if(max < a.at(i)) {
            max = a.at(i);
        }
    }
    return max;
}

int nadjiBrojCifara(int max) {
    int brojCifara = 0;
    while(max != 0) {
        max /= 10;
        brojCifara++;
    }
    return brojCifara;
}

void radixSort(std::vector<int> &a) {
    int maxBrojCifara = nadjiBrojCifara(nadjiMax(a));
    //std::cout << maxBrojCifara;
    std::vector<std::vector<int>> Q(10);
    for(int j=0; j<maxBrojCifara; j++) {
        // npr za broj 21 da dobijemo 2 podijelimo broj s 10 i uzmemo ostatak pri dijeljenju s 10
        int dijeliSa = pow(10, j);
        for(int i = 0; i<a.size(); i++) {
            int cifra = (a.at(i) / dijeliSa) % 10;
            //std::cout << "\n Element: " << a.at(i) << ", dijeli sa: " << dijeliSa << ", cifra: " << cifra;
            Q.at(cifra).push_back(a.at(i));
        }
        // brojac da brojimo elemente koje stavljamo u vektor a(u petlji j se koristi)
        int brojac{};
        for(int i=0; i<Q.size(); i++) {
            for(int j=0; j<Q.at(i).size(); j++) {
                a.at(brojac++) = Q.at(i).at(j);
            }
            Q.at(i).clear();
        }
    }
}

bool daLiJeList(std::vector<int> &a, int i, int vel) {
    return (i>=(vel / 2) && i < vel);
}

int roditelj(int i) {
    return (i - 1) / 2;
}

int desnoDijete(int i) {
    return 2 * i + 2;
}

int lijevoDijete(int i) {
    return 2 * i + 1;
}

void popraviDolje(std::vector<int> &a, int i, int velicina) {
    while(!daLiJeList(a, i, velicina)) {
        int dd = desnoDijete(i);
        int veci = lijevoDijete(i);
        if(dd < velicina && a.at(dd) > a.at(veci)) {
            veci = dd;
        }
        if(a.at(i) > a.at(veci)) {
            return;
        }
        std::swap(a.at(i), a.at(veci));
        i = veci;
    }
}

void stvoriGomilu(std::vector<int> &a) {
    int velicina = a.size();
    for(int i=(velicina/2) - 1; i>=0; i--) {
        popraviDolje(a, i, velicina);
    }
}

void popraviGore(std::vector<int> &a, int i) {
    while(i != 0 && a.at(i) > a.at(roditelj(i))) {
        std::swap(a.at(i), a.at(roditelj(i)));
        i = roditelj(i);
    }
}

void umetniUGomilu(std::vector<int> &a, int umetnuti, int &velicina) {
    if(a.size() < velicina) {
        throw std::overflow_error("Gomila je puna!");
    }
    a.push_back(umetnuti);
    popraviGore(a, (++velicina) - 1);
}

int izbaciPrvi(std::vector<int> &a, int &velicina) {
    if(velicina == 0) {
        throw std::domain_error("Gomila je prazna!");
    }
    velicina--;
    std::swap(a.at(0), a.at(velicina));
    if(velicina != 0) {
        popraviDolje(a, 0, velicina);
    }
    return a.at(velicina);
}

void gomilaSort(std::vector<int> &a) {
    stvoriGomilu(a);
    int velicina = a.size();
    for(int i=a.size() - 1; i>0; i--) {
        std::swap(a.at(0), a.at(i));
        popraviDolje(a, 0, --velicina);
    }
}

int main() {
    std::vector<int> a = {45,987,12368,45,678,123,1096};
    std::vector<int> b = {546,987,132,45,1,6897,312,130,131,132,133,134,137,135};
    gomilaSort(b);
    std::cout << "\nGomila b ima sljedece elemente: ";
    for(auto x : b) {
        std::cout << x << " ";
    }
    std::cout << "\nA sada gomila b izgleda: ";
    //stvoriGomilu(b);
    for(auto x : b) {
        std::cout << x << " ";
    }
    stvoriGomilu(a);
    int velicina = a.size();
    umetniUGomilu(a, 124, velicina);
    umetniUGomilu(a, 354, velicina);
    umetniUGomilu(a, 687, velicina);
    std::cout << "\nGomila a ima sljedece elemente: ";
    for(auto x : a) {
        std::cout << x << " ";
    }
    std::cout << "\nNakon izbacivanja: ";
    izbaciPrvi(a, velicina);
    for(auto x : a) {
        std::cout << x << " ";
    }
    radixSort(a);
    std::cout << "\nNakon radix sortiranja: ";
    for(auto x : a) {
        std::cout << x << " ";
    }
    return 0;
}