#include <iostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include <ctime>

void Goldbach (int n, int& p, int& q) {
    if(n % 2 != 0 || n <= 2) throw std::logic_error("Uneseni broj je pogresan");
    std::vector<int> vek{2};
    for(int i=2; i<=n-2; i++) {
        bool prost{true};
        for(int j=2; j <= std::sqrt(i); j++) {
            if(i % j == 0) { 
                prost = false;
                break;
            }
        }
        if(prost == true) vek.push_back(i);
    }

    // std::cout << std::endl;
    // for(int x : vek) {
    //     std::cout << x << "   ";
    // }
    //std::cout << "\nN: " << n << "N";
    p = 1;
    q = 1;
    for(int i=0; i<vek.size(); i++) {
        for(int j=0; j<vek.size(); j++) {
            //std::cout << "\n vek[i] = " << vek[i] << "\tvek[j]= " << vek[j];
            if(vek.at(i) + vek.at(j) == n) {
                //std::cout << "\nP: " << p << " Q:  " << q;
                p = vek.at(i);
                q = vek.at(j);
                return;
            }
        }
    }
    if(p == 1) throw std::logic_error("");
}

int main() {
    std::cout << "Unesite neki broj: ";


    int p, q;
    int n{};
    do {
        std::cin >> n;
        clock_t vrijeme1 = clock();
        Goldbach(n,p,q);
        clock_t vrijeme2 = clock();
        double ukvrijeme = static_cast<double>(vrijeme2 - vrijeme1) / (CLOCKS_PER_SEC / 1000);
        std::cout << "Vrijeme izvrsenja: " << ukvrijeme << " ms." << std::endl;
    } while(n != 0);
    // try {
    //     Goldbach(n, p, q);
    //     std::cout << std::endl << "P iznosi: " << p << ", a Q iznosi: " << q << std::endl;
    // } catch(std::logic_error e) {
    //     std::cout << e.what() << std::endl;
    // }
    return 0;
}