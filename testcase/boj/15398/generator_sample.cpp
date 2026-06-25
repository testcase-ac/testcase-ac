#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int pickCost(int mode, int i, int n) {
    if (mode == 0) {
        return rnd.next(1, 20);
    }
    if (mode == 1) {
        return (i % 3 == 0) ? 1 : rnd.next(2, 50);
    }
    if (mode == 2) {
        return (i % 4 == 0) ? 1000000000 : rnd.next(999999950, 1000000000);
    }
    if (mode == 3) {
        int base = rnd.next(1, 12);
        return base * base;
    }

    int rank = (i * 1000) / max(1, n - 1);
    if (rnd.next(2) == 0) {
        rank = 1000 - rank;
    }
    return max(1, rank + rnd.next(0, 25));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else if (mode == 2) {
        n = rnd.next(7, 14);
    } else {
        n = rnd.next(15, 30);
    }

    vector<int> costs(n);
    int costMode = rnd.next(0, 4);
    for (int i = 0; i < n; ++i) {
        costs[i] = pickCost(costMode, i, n);
    }
    if (rnd.next(4) == 0) {
        shuffle(costs.begin(), costs.end());
    }

    string a(n, '0');
    string b(n, '0');
    for (int i = 0; i < n; ++i) {
        int state;
        if (mode == 3) {
            state = rnd.next(0, 2) == 0 ? 1 : 2;
        } else if (mode == 4) {
            state = rnd.next(0, 2) == 0 ? 0 : 3;
        } else if (mode == 5) {
            state = i % 4;
        } else if (mode == 6) {
            state = (i + rnd.next(0, 1)) % 4;
        } else {
            state = rnd.next(0, 3);
        }

        if (state == 0) {
            a[i] = '0';
            b[i] = '0';
        } else if (state == 1) {
            a[i] = '0';
            b[i] = '1';
        } else if (state == 2) {
            a[i] = '1';
            b[i] = '0';
        } else {
            a[i] = '1';
            b[i] = '1';
        }
    }

    if (mode == 0 && rnd.next(2) == 0) {
        a[0] = '1';
        b[0] = rnd.next(2) == 0 ? '0' : '1';
    }

    println(n);
    println(costs);
    println(a);
    println(b);

    return 0;
}
