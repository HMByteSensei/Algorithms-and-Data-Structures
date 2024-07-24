#ifndef SORTING_H
#define SORTING_H

#include <string>

template <typename Tip>
void bubble_sort(Tip* niz, int vel) {
    for(int i=vel-1; i >= 1; i--) {
        for(int j=1; j <= i; j++) {
            if(niz[j-1] > niz[j]) {
                Tip el = niz[j-1];
                niz[j-1] = niz[j];
                niz[j] = el;
            }
        }
    }
}

template <typename Tip>
void selection_sort(Tip* niz, int vel) {
    for(int i=0; i<=vel-2; i++) {
        Tip min = niz[i];
        int pmin = i;
        for(int j=i+1; j<=vel-1; j++) {
            if(niz[j] < min) {
                min = niz[j];
                pmin = j;
            }
        }
        niz[pmin] = niz[i];
        niz[i] = min;
    }
}

template <typename Tip>
int particija(Tip* niz, int prvi, int zadnji) {
    Tip pivot = niz[prvi];
    int p = prvi + 1;
    while(p <= zadnji && niz[p] < pivot) {
        p += 1;
    }
    for(int i = p+1; i<=zadnji; i++) {
        if(niz[i] < pivot) {
            Tip el = niz[i];
            niz[i] = niz[p];
            niz[p] = el;
            p += 1;
        }
    }
    Tip el = niz[prvi];
    niz[prvi] = niz[p-1];
    niz[p-1] = el;
    return p-1;
}

template <typename Tip>
void quick_sort(Tip* niz, int vel) {
    static int prvi = 0;
    static int zadnji = vel - 1;
    //std::cout << "\nPrvi " << prvi << " zadnji " << zadnji;
    if(prvi < zadnji) {
        int j = particija(niz, prvi, zadnji);
        int temp = zadnji;
        zadnji = j - 1;
        quick_sort(niz, j-1);
        zadnji = temp;
        prvi = j+1;
        quick_sort(niz, zadnji);
    }
}

template <typename Tip>
void merge(Tip *niz, int l, int p, int q, int u) {
    int i = 0;
    int j = q - l;
    int k = l;
    Tip *pomocni = new Tip[u - l + 1];
    for(int m = 0; m <= u - l; m++) {
        pomocni[m] = niz[l + m];
    }
    while(i <= p - l && j <= u - l) {
        if(pomocni[i] < pomocni[j]) {
            niz[k] = pomocni[i];
            i = i + 1;
        } else {
            niz[k] = pomocni[j];
            j = j + 1;
        }
        k += 1;
    }
    while(i <= p - l) {
        niz[k] = pomocni[i];
        k = k + 1;
        i = i + 1;
    }
    while(j <= u - l) {
        niz[k] = pomocni[j];
        k = k + 1;
        j = j + 1;
    }
    delete[] pomocni;
}

template <typename Tip>
void merge_helper(Tip *niz, int l, int u) {
    if(u > l) {
        int p = (l+u-1) / 2;
        int q = p + 1;
        merge_helper(niz, l, p);
        merge_helper(niz, q, u);
        merge(niz, l, p, q, u);
    }
}

template <typename Tip>
void merge_sort(Tip* niz, int vel) {
    merge_helper(niz, 0, vel-1);
}

#endif