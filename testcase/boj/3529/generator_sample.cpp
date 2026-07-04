#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> bases;
    for (int base = 2; base <= 10; ++base) {
        bases.push_back(base);
    }
    shuffle(bases.begin(), bases.end());

    int mode = rnd.next(0, 4);
    int total;
    if (mode == 0) {
        total = rnd.next(2, 4);
    } else if (mode == 1) {
        total = rnd.next(5, 7);
    } else if (mode == 2) {
        total = rnd.next(8, 9);
    } else {
        total = rnd.next(2, 9);
    }

    int n;
    if (mode == 3) {
        n = rnd.next(1, total - 1);
    } else if (mode == 4) {
        n = rnd.next(max(1, total / 2 - 1), min(8, min(total - 1, total / 2 + 1)));
    } else {
        n = rnd.next(1, min(8, total - 1));
    }
    int m = total - n;

    vector<int> good, bad;
    for (int i = 0; i < n; ++i) {
        good.push_back(bases[i]);
    }
    for (int i = 0; i < m; ++i) {
        bad.push_back(bases[n + i]);
    }
    shuffle(good.begin(), good.end());
    shuffle(bad.begin(), bad.end());

    println(n, m);
    println(good);
    println(bad);

    return 0;
}
