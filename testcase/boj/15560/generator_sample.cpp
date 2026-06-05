#include "testlib.h"
#include <vector>
using namespace std;

int boundedValue(int lo, int hi) {
    return rnd.next(lo, hi);
}

int patternedValue(int mode) {
    if (mode == 0) return rnd.next(-3, 3);
    if (mode == 1) return rnd.any(vector<int>{-100, -50, 0, 50, 100});
    if (mode == 2) return rnd.next(-100, -80);
    if (mode == 3) return rnd.next(80, 100);
    return rnd.next(-100, 100);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else {
        n = rnd.next(6, 25);
    }

    int q = (mode == 0) ? rnd.next(1, 4) : rnd.next(n, min(45, n * 3 + 5));
    int u = rnd.any(vector<int>{-5, -2, -1, 0, 1, 2, 5});
    int v = rnd.any(vector<int>{-5, -3, 0, 3, 5});

    vector<int> k(n);
    int valueMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        if (mode == 1 && i % 2 == 0) {
            k[i] = patternedValue(2);
        } else if (mode == 1) {
            k[i] = patternedValue(3);
        } else {
            k[i] = patternedValue(valueMode);
        }
    }

    println(n, q, u, v);
    println(k);

    for (int i = 0; i < q; ++i) {
        bool makeQuery;
        if (mode == 4) {
            makeQuery = rnd.next(0, 4) != 0;
        } else if (mode == 5) {
            makeQuery = rnd.next(0, 4) == 0;
        } else {
            makeQuery = rnd.next(0, 1) == 0;
        }

        int a = rnd.next(1, n);
        if (makeQuery) {
            int b = rnd.next(a, n);
            println(0, a, b);
        } else {
            int b = patternedValue(rnd.next(0, 4));
            println(1, a, b);
        }
    }

    return 0;
}
