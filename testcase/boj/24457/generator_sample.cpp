#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 24);
    if (mode == 6) n = rnd.next(25, 80);

    vector<int> e(n), c(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            e[i] = rnd.next(0, 12);
            c[i] = rnd.next(0, 12);
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            e[i] = rnd.next(0, 3);
            c[i] = rnd.next(10, 80);
        }
    } else if (mode == 2) {
        int caffeine = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            e[i] = rnd.next(0, 200);
            c[i] = caffeine;
        }
    } else if (mode == 3) {
        int baseC = rnd.next(0, 8);
        int baseE = rnd.next(0, 20);
        for (int i = 0; i < n; ++i) {
            e[i] = baseE + i * rnd.next(1, 8) + rnd.next(0, 5);
            c[i] = baseC + i * rnd.next(1, 6);
        }
    } else if (mode == 4) {
        int caffeine = 0;
        for (int i = 0; i < n; ++i) {
            caffeine += rnd.next(0, 10);
            e[i] = max(0, caffeine + rnd.next(-15, 30));
            c[i] = rnd.next(0, 30);
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            e[i] = rnd.any(vector<int>{0, 1, 999999, 1000000, rnd.next(0, 1000000)});
            c[i] = rnd.any(vector<int>{0, 1, 999999, 1000000, rnd.next(0, 1000000)});
        }
    } else {
        int maxValue = rnd.next(50, 1000000);
        for (int i = 0; i < n; ++i) {
            e[i] = rnd.next(0, maxValue);
            c[i] = rnd.next(0, maxValue);
        }
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    vector<int> shuffledE(n), shuffledC(n);
    for (int i = 0; i < n; ++i) {
        shuffledE[i] = e[order[i]];
        shuffledC[i] = c[order[i]];
    }

    println(n);
    println(shuffledE);
    println(shuffledC);
    return 0;
}
