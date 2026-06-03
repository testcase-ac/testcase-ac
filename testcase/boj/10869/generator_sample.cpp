#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int a, b;

    if (mode == 0) {
        a = rnd.next(1, 20);
        b = rnd.next(1, 20);
    } else if (mode == 1) {
        b = rnd.next(1, 100);
        a = b * rnd.next(1, 10000 / b);
    } else if (mode == 2) {
        b = rnd.next(2, 10000);
        a = rnd.next(1, b - 1);
    } else if (mode == 3) {
        b = rnd.next(1, 100);
        a = rnd.next(max(1, b - 5), min(10000, b + 5));
    } else if (mode == 4) {
        a = rnd.next(9900, 10000);
        b = rnd.next(1, 10000);
    } else {
        a = rnd.next(1, 10000);
        b = rnd.next(9900, 10000);
    }

    println(a, b);
    return 0;
}
