#include "testlib.h"

#include <numeric>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int p;
    int q;

    if (mode == 0) {
        p = rnd.next(1, 12);
        q = p * rnd.next(1, 100 / p);
    } else if (mode == 1) {
        int base = rnd.next(1, 20);
        p = base * rnd.next(1, 100 / base);
        q = base * rnd.next(1, 100 / base);
    } else if (mode == 2) {
        p = rnd.next(80, 100);
        q = rnd.next(80, 100);
    } else if (mode == 3) {
        p = rnd.next(1, 10);
        q = rnd.next(90, 100);
    } else {
        p = rnd.next(1, 100);
        q = rnd.next(1, 100);
    }

    int lcm = p / gcd(p, q) * q;
    int s;

    if (mode == 0) {
        s = rnd.next(lcm, 10000);
    } else if (mode == 1) {
        s = max(1, lcm - rnd.next(1, min(lcm, 50)));
    } else if (mode == 2) {
        s = rnd.next(1, min(10000, lcm));
    } else if (mode == 3) {
        s = min(10000, lcm + rnd.next(0, 50));
    } else if (mode == 4) {
        s = rnd.next(1, 30);
    } else if (mode == 5) {
        s = rnd.next(5000, 10000);
    } else {
        s = rnd.next(1, 10000);
    }

    println(p, q, s);

    return 0;
}
