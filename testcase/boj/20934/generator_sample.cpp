#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(6, 25);
    } else if (mode == 2) {
        n = rnd.next(10, 45);
    } else if (mode == 3) {
        n = rnd.next(20, 80);
    } else if (mode == 4) {
        n = rnd.next(30, 120);
    } else {
        n = rnd.next(80, 200);
    }

    vector<int> c(n);
    if (mode == 0) {
        for (int i = 0; i < n; ++i) c[i] = rnd.next(1, 5);
    } else if (mode == 1) {
        int value = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) c[i] = value;
    } else if (mode == 2) {
        int first = rnd.next(1, 5);
        int second = rnd.next(1, 5);
        if (first == second) second = second % 5 + 1;
        for (int i = 0; i < n; ++i) c[i] = (i % 2 == 0 ? first : second);
    } else if (mode == 3) {
        int cycle = rnd.next(2, 5);
        vector<int> pattern(cycle);
        for (int i = 0; i < cycle; ++i) pattern[i] = rnd.next(1, 5);
        for (int i = 0; i < n; ++i) c[i] = pattern[i % cycle];
    } else if (mode == 4) {
        int lo = rnd.next(1, 3);
        int hi = rnd.next(lo, 5);
        for (int i = 0; i < n; ++i) c[i] = rnd.next(lo, hi);
    } else {
        for (int i = 0; i < n; ++i) {
            c[i] = (rnd.next(0, 99) < 70 ? rnd.next(1, 2) : rnd.next(3, 5));
        }
    }

    int tailBoost = rnd.next(0, 3);
    for (int k = 0; k < tailBoost && k < n; ++k) {
        c[n - 1 - k] = rnd.next(4, 5);
    }

    println(n);
    println(c);
    return 0;
}
