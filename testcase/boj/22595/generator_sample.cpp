#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 4);
    } else {
        n = rnd.next(5, 12);
    }

    vector<vector<int>> cost(n, vector<int>(n, 0));
    int baseLimit = rnd.next(3, 200);

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int a = 0;
            int b = 0;

            if (mode == 1) {
                a = rnd.next(0, baseLimit);
                b = rnd.next(0, baseLimit);
            } else if (mode == 2) {
                int base = rnd.next(0, baseLimit);
                int delta = rnd.next(0, 5);
                a = min(1000000, base + delta);
                b = min(1000000, base + rnd.next(0, 5));
            } else if (mode == 3) {
                a = (i < j) ? rnd.next(0, 20) : rnd.next(80, 300);
                b = (i < j) ? rnd.next(80, 300) : rnd.next(0, 20);
            } else if (mode == 4) {
                a = rnd.next(0, 4) == 0 ? 0 : rnd.next(1, baseLimit);
                b = rnd.next(0, 4) == 0 ? 0 : rnd.next(1, baseLimit);
            } else {
                int high = rnd.next(1000, 1000000);
                a = rnd.next(0, 2) == 0 ? rnd.next(0, 100) : high;
                b = rnd.next(0, 2) == 0 ? rnd.next(0, 100) : rnd.next(1000, 1000000);
            }

            cost[i][j] = a;
            cost[j][i] = b;
        }
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        println(cost[i]);
    }

    return 0;
}
