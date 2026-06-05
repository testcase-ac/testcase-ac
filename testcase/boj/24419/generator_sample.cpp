#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(16, 24);
    } else {
        n = rnd.next(5, 18);
    }

    vector<vector<int>> m(n, vector<int>(n));
    int base = rnd.next(1, 100000);
    int step = rnd.next(1, 997);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int value;
            if (mode == 0) {
                value = rnd.next(1, 9);
            } else if (mode == 1) {
                value = base;
            } else if (mode == 2) {
                value = 1 + ((i + j) * step + base) % 100000;
            } else if (mode == 3) {
                value = (i == j || i + j == n - 1) ? 100000 : rnd.next(1, 50);
            } else if (mode == 4) {
                value = ((i + j) % 2 == 0) ? rnd.next(99900, 100000) : rnd.next(1, 100);
            } else {
                value = rnd.next(1, 100000);
            }
            m[i][j] = value;
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(m[i]);
    }

    return 0;
}
