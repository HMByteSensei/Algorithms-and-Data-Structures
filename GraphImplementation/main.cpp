#include "GranaIterator.h"
#include "MatricaGraf.h"
#include "DFS.h"
#include "BFS.h"
#include "UsmjereniGraf.h"
#include "Grana.h"
#include "Cvor.h"

using namespace std;

int main() {
    UsmjereniGraf<std::string> *g = new MatricaGraf<std::string>(4);
    g->dodajGranu(0, 1, 2.5);
    g->dodajGranu(1, 2, 1.2);
    g->dodajGranu(1, 3, 0.1);
    g->dodajGranu(3, 3, -4.0);
    g->postaviOznakuGrane(3, 3, "aa");
    g->dajGranu(0,1).postaviOznaku("bb");
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (g->postojiGrana(i,j))
                cout << "(" << i << "," << j << ") -> '" << g->dajOznakuGrane(i, j) << "','" << g->dajGranu(i, j).dajOznaku() << "'; ";
    delete g;
}