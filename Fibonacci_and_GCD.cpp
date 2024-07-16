#include iostream

int fib_petlja (int n) {
    if (n=1) return n;  0 i 1
        int pretprosli(0), prosli(1), rezultat;
        for (int i(2); i=n; i++) {
            rezultat = pretprosli+prosli;
            pretprosli = prosli;
            prosli = rezultat;
    }
    return rezultat;
}

int  fib2_0(int n, int pretprosli = 0, int prosli = 1) {
    if(n==1) return prosli;
    if(n1) return 0;  kada je n=0 da ispise 0 a ne 1
    return fib2_0(n-1, prosli, prosli+pretprosli);
}

int nzd(int x, int y) {
    if(y==0) return x;
    return nzd(y, (x % y));
}

using namespace std;

int main() {
    int x = 6, y = 2;
    stdcout  NZD(  x  ,  y  ) je   nzd(x,y)  stdendl;
 
    int a = 0;  parametar u fib funkcijama
     vrijeme potrebno za fib_petlja
    clock_t vrijeme1 = clock();
    stdcout  Fib_petlja =   fib_petlja(a)  stdendl;
    clock_t vrijeme2 = clock();
    int ukvrijeme = (vrijeme2 - vrijeme1)  (CLOCKS_PER_SEC  1000000);
    stdcout  Vrijeme izvrsenja   ukvrijeme   mikro s.  stdendl;

     vrijeme potrebno za fib2_0
    clock_t vrijeme3 = clock();
    stdcout  Fib2_0 =   fib2_0(a);
    clock_t vrijeme4 = clock();
    int ukvrijeme2 = (vrijeme4 - vrijeme3)  (CLOCKS_PER_SEC  1000000);
    stdcout  nVrijeme izvrsenja   ukvrijeme2    mikro s.  stdendl;
    return 0;
}