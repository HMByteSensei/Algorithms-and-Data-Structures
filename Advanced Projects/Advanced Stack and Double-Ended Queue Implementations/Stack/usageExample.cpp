#include "Stek.h"
#include <vector>

int main() {
    Stek<std::vector<int>> s;
    generiraj(1, 5, s);
    pretraga(s, 10);
    std::cout << "\n";
    pretraga(s, 11);
    std::cout << "\n";
    pretraga(s, 3425);
    prikaziStek(s);
    return 0;
}