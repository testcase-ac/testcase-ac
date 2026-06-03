#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 5;
    } else if (mode == 1) {
        n = 15;
    } else if (mode <= 3) {
        n = rnd.next(5, 8);
    } else {
        n = rnd.next(9, 15);
    }

    vector<vector<int>> m(n, vector<int>(n));
    int base = rnd.next(1, 100000);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (mode == 0) {
                m[i][j] = rnd.next(1, 9);
            } else if (mode == 1) {
                m[i][j] = rnd.next(99900, 100000);
            } else if (mode == 2) {
                m[i][j] = min(100000, 1 + i * rnd.next(1, 20) + j * rnd.next(1, 20));
            } else if (mode == 3) {
                m[i][j] = min(100000, base + (i == j ? rnd.next(0, 500) : rnd.next(0, 30)));
            } else if (mode == 4) {
                m[i][j] = (i + j) % 2 == 0 ? rnd.next(1, 50) : rnd.next(99950, 100000);
            } else if (mode == 5) {
                m[i][j] = min(100000, 1 + (n - 1 - i) * rnd.next(1, 25) + j * rnd.next(1, 25));
            } else if (mode == 6) {
                int lo = rnd.next(1, 99900);
                m[i][j] = rnd.next(lo, min(100000, lo + rnd.next(0, 100)));
            } else {
                m[i][j] = rnd.next(1, 100000);
            }
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(m[i]);
    }

    return 0;
}
