#ifndef DFS_H
#define DFS_H

#include "GranaIterator.h"

//DFS
template<typename Tip>
void dfs(UsmjereniGraf<Tip> *ug, std::vector<Cvor<Tip>> &obilazak, Cvor<Tip> c) {
    c.postaviOznaku(1);
    obilazak.push_back(c);
    for(GranaIterator<Tip> iter = ug->dajGranePocetak(); iter != ug->dajGraneKraj(); iter++) {
        if((*iter).dajPolazniCvor().dajRedniBroj() == c.dajRedniBroj() && (*iter).dajDolazniCvor().dajOznaku() != 1) {
            dfs(ug, obilazak, (*iter).dajDolazniCvor());
        }
    }
}

#endif