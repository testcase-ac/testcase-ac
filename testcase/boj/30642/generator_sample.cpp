#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    string mascot = rnd.next(0, 1) == 0 ? "annyong" : "induck";
    int k;

    if (mode == 0) {
        n = 2;
        k = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = rnd.next(1, n);
    } else if (mode == 2) {
        n = rnd.next(2, 40);
        bool wantOdd = mascot == "annyong";
        k = rnd.next(1, (n + (wantOdd ? 1 : 0)) / 2) * 2 - (wantOdd ? 1 : 0);
        if (k > n) k -= 2;
    } else if (mode == 3) {
        n = rnd.next(2, 40);
        k = rnd.next(0, 1) == 0 ? 1 : n;
    } else if (mode == 4) {
        n = rnd.next(19980, 20000);
        k = rnd.next(1, n);
    } else {
        n = rnd.next(2, 20000);
        k = rnd.next(1, n);
    }

    println(n);
    println(mascot);
    println(k);

    return 0;
}
