#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 4);
        m = rnd.next(2, 4);
    } else if (mode == 3) {
        n = rnd.next(8, 15);
        m = rnd.next(8, 15);
    } else if (mode == 4) {
        n = rnd.next(2, 15);
        m = rnd.next(2, 15);
        if (rnd.next(0, 1)) {
            n = rnd.next(35, 50);
        } else {
            m = rnd.next(35, 50);
        }
    } else {
        n = rnd.next(1, 50);
        m = rnd.next(1, 50);
    }

    vector<pair<int, int>> favored = {
        {1, 1},
        {1, m},
        {n, 1},
        {n, m},
        {(n + 1) / 2, (m + 1) / 2},
    };

    int r;
    int c;
    if (rnd.next(0, 99) < 45) {
        auto cell = rnd.any(favored);
        r = cell.first;
        c = cell.second;
    } else {
        r = rnd.next(1, n);
        c = rnd.next(1, m);
    }

    println(n, m);
    for (int i = 1; i < n; ++i) {
        println(abs(r - i) + abs(c - 1));
    }

    vector<int> bottom;
    for (int j = 1; j <= m; ++j) {
        bottom.push_back(abs(r - n) + abs(c - j));
    }
    println(bottom);

    return 0;
}
