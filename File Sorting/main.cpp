#include <iostream>
#include <ctime>
#include "sorting.h"
#include "file_operations.h"

void meni() {
    std::cout << "\nUnesite 1 da se generira fajl sa random brojevima ili 2 da se sortira vec postojeca datoteka s elementima (0 za izlaz): ";
    int izbor1{};
    // default datoteka u kojoj cemo smjestati elemente nasumicno generiranog niza
    std::string fajl = "nasumicno_generirani.txt";
    
    while(std::cin >> izbor1) {
        if(izbor1 == 0) {
            exit(0);
        } else if(izbor1 == 1) { 
            std::cout << "Unesite velicinu niza koji se generira: ";
            int vel;
            std::cin >> vel;
            generisi(fajl, vel);
            break;
        } else if(izbor1 == 2) {
            std::cout << "Unesite ime fajla koji zelite sortirati: ";
            std::cin.ignore(1000, '\n');
            std::getline(std::cin, fajl);
            break;
        } else {
            std::cout << "GRESKA POGRESAN IZBOR";
            std::cin.ignore(1000, '\n');
            std::cin.ignore();
        }
    }
    int *niz;
    int vel;
    ucitaj(fajl, niz, vel);

    std::cout << "\nKoji nacin sortiranja zelite da primjenite:";
    std::cout << "\n1 - bubble_sort";
    std::cout << "\n2 - selection_sort";
    std::cout << "\n3 - quick_sort";
    std::cout << "\n4 - merge_sort\nUnesite izbor: ";

    int izbor2{};
    std::cin >> izbor2;
    if(izbor2 == 1) bubble_sort(niz, vel);
    else if(izbor2 == 2) selection_sort(niz, vel);
    else if(izbor2 == 3) quick_sort(niz, vel);
    else if(izbor2 == 4) merge_sort(niz, vel);
    else {
        std::cout << "\nGRESKA: POGRESAN BROJ";
        std::cin.ignore(1000, '\n');
        std::cin.clear();
    }
    std::cout << "Provjeravanje da li je niz sortiran...";
    std::cout << (daLiJeSortiran(niz, vel) ? "\nSve spremno niz sortiran" : "\nDoslo je do poteskoca prilikom sortiranja");
    std::cout << "\nUnesite fajl u kojem zelite da cuvate sortirani niz(ENTER za default fajl): ";
    std::string sortiraniFajl;
    std::cin.ignore(1000, '\n');
    if( (std::getline(std::cin, sortiraniFajl)) && sortiraniFajl.empty()) {
        zapisi(niz, vel);
    } else {
        zapisi(niz, vel, sortiraniFajl);
    }
}


int main() {
    while(true){
        clock_t vrijeme1 = clock();
        meni();
        clock_t vrijeme2 = clock();
        int ukvrijeme = (vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000000);
        std::cout << "\nVrijeme izvrsenja: " << ukvrijeme << " mikro sekundi." << std::endl;
    }

    return 0;
}