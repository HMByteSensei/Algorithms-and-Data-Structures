#ifndef BFS_H
#define BFS_H

#include "GranaIterator.h"

template<typename Tip>
void obradiSusjedni(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, std::queue<Cvor<Tip>> &q, Cvor<Tip> c) {
    GranaIterator<Tip> grana = ug->dajGranePocetak();

    for(auto pom = grana; pom != ug->dajGraneKraj(); pom++) {
        auto start = (*pom).dajPolazniCvor();
        auto end = (*pom).dajDolazniCvor();
    
        if(end.dajOznaku() != 1 && start.dajRedniBroj() == c.dajRedniBroj()) {
            end.postaviOznaku(1);
            obilazak.push_back(end);
            q.push(end);
        }
    }
}

// BFS
template<typename Tip>
void recursiveBFS(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, std::queue<Cvor<Tip>> &q);

template <typename Tip>
void bfs(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, Cvor<Tip> cvor) {
    cvor.postaviOznaku(1);
    obilazak.push_back(cvor);
    std::queue<Cvor<Tip>> red;
    red.push(cvor);
    recursiveBFS(ug, obilazak, red);
}

template<typename Tip>
void recursiveBFS(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, std::queue<Cvor<Tip>> &q) {
    if(q.empty()) {
        return;
    }
    Cvor<Tip> c = q.front();
    q.pop();
    obradiSusjedni(ug, obilazak, q, c);

    recursiveBFS(ug, obilazak, q);
}

#endif