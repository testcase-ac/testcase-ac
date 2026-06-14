#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomN() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return rnd.next(1, 3);
    if (mode == 1) return rnd.next(4, 20);
    if (mode == 2) return rnd.next(21, 200);
    if (mode == 3) return rnd.next(1000, 5000);
    if (mode == 4) return rnd.next(90000, 100000);
    return rnd.next(1, 100000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxV = 100000;
    int mode = rnd.next(0, 8);
    int p = 1, q = 1, n = randomN();

    if (mode == 0) {
        p = q = rnd.next(1, maxV);
    } else if (mode == 1) {
        q = rnd.next(2, maxV);
        p = rnd.next(1, q - 1);
    } else if (mode == 2) {
        p = rnd.next(2, maxV);
        q = rnd.next(1, p - 1);
    } else if (mode == 3) {
        q = rnd.next(50000, maxV);
        p = rnd.next(1, 20);
    } else if (mode == 4) {
        p = rnd.next(50000, maxV);
        q = rnd.next(1, 20);
    } else if (mode == 5) {
        vector<int> values = {1, 2, 3, 10, 99991, 100000};
        p = rnd.any(values);
        q = rnd.any(values);
    } else if (mode == 6) {
        int base = rnd.next(1, 200);
        int scale = rnd.next(1, maxV / base);
        p = base * scale;
        q = rnd.next(1, maxV / base) * base;
    } else if (mode == 7) {
        p = rnd.next(99900, maxV);
        q = rnd.next(99900, maxV);
    } else {
        p = rnd.next(1, maxV);
        q = rnd.next(1, maxV);
    }

    println(p, q, n);
    return 0;
}
