#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int a;
    int b;

    if (mode == 0) {
        n = rnd.next(1, 8);
        a = rnd.next(1, 20);
        b = 1;
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        int g = rnd.next(2, 20);
        a = g * rnd.next(1, 20);
        b = g * rnd.next(1, 20);
    } else if (mode == 2) {
        n = rnd.next(1, 12);
        b = rnd.next(2, 30);
        a = rnd.next(1, 30);
        while (__gcd(a, b) != 1) {
            a = rnd.next(1, 30);
        }
    } else if (mode == 3) {
        n = rnd.next(1, 20);
        a = rnd.next(1, 100);
        b = rnd.next(1, 100);
    } else if (mode == 4) {
        vector<int> ns = {1, 2, 99999, 100000};
        n = rnd.any(ns);
        a = rnd.next(999999900, 1000000000);
        b = rnd.next(999999900, 1000000000);
    } else if (mode == 5) {
        n = rnd.next(1, 15);
        int base = rnd.next(1, 500);
        a = base;
        b = base + rnd.next(1, 20);
    } else {
        n = rnd.next(1, 30);
        a = rnd.next(1, 1000000000);
        b = rnd.next(1, 1000000000);
    }

    println(n, a, b);
    return 0;
}
