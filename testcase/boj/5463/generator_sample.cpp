#include "testlib.h"

#include <vector>
using namespace std;

int boundedValue(int base, int delta) {
    int value = base + rnd.next(-delta, delta);
    if (value < 1) return 1;
    if (value > 1000) return 1000;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = 1;
        m = 1;
    } else if (mode == 1) {
        n = 1;
        m = rnd.next(2, 10);
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        m = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 4);
        m = rnd.next(5, 10);
    } else if (mode == 4) {
        n = rnd.next(5, 10);
        m = rnd.next(2, 4);
    } else {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    }

    vector<vector<int>> raisins(n, vector<int>(m, 1));
    int pattern = rnd.next(0, 5);
    int base = rnd.next(1, 1000);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (pattern == 0) {
                raisins[i][j] = boundedValue(base, 3);
            } else if (pattern == 1) {
                raisins[i][j] = rnd.next(1, 12);
            } else if (pattern == 2) {
                raisins[i][j] = rnd.next(900, 1000);
            } else if (pattern == 3) {
                raisins[i][j] = 1 + ((i + 1) * (j + 2) + rnd.next(0, 5)) % 30;
            } else if (pattern == 4) {
                raisins[i][j] = (rnd.next(0, 99) < 80 ? rnd.next(1, 8) : rnd.next(700, 1000));
            } else {
                raisins[i][j] = rnd.next(1, 1000);
            }
        }
    }

    println(n, m);
    for (int i = 0; i < n; ++i) {
        println(raisins[i]);
    }

    return 0;
}
