#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static void printCase(int n, vector<int> a) {
    println(n, (int)a.size());
    println(a);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(1, 12);
    int n = rnd.next(1, 20);
    vector<int> a;

    if (mode == 0) {
        m = rnd.next(1, 12);
        n = rnd.next(m, min(30, m + 18));
        a.assign(m, 4);
        int extraTables = n - m;
        for (int i = 0; i < extraTables; ++i) {
            a[rnd.next(0, m - 1)] += 4;
        }
        for (int& x : a) {
            x += rnd.next(0, 3);
        }
    } else if (mode == 1) {
        m = rnd.next(2, 12);
        n = rnd.next(1, m - 1);
        a.resize(m);
        for (int& x : a) {
            x = rnd.next(4, 40);
        }
    } else if (mode == 2) {
        m = rnd.next(1, 12);
        n = rnd.next(m + 1, min(30, m + 18));
        a.assign(m, 4);
        int targetTables = rnd.next(m, n - 1);
        for (int i = m; i < targetTables; ++i) {
            a[rnd.next(0, m - 1)] += 4;
        }
        for (int& x : a) {
            x += rnd.next(0, 3);
        }
    } else if (mode == 3) {
        m = rnd.next(1, 12);
        n = rnd.next(1, 20);
        a.resize(m);
        for (int& x : a) {
            x = rnd.next(1, 100);
        }
        a[rnd.next(0, m - 1)] = rnd.next(1, 3);
    } else if (mode == 4) {
        m = rnd.next(1, 20);
        n = rnd.next(1, 25);
        a.resize(m);
        int base = rnd.next(1, 24);
        for (int& x : a) {
            x = min(100, 4 * rnd.next(0, base) + rnd.next(0, 3));
            x = max(1, x);
        }
    } else {
        m = rnd.next(80, 100);
        n = rnd.next(80, 100);
        a.resize(m);
        for (int& x : a) {
            x = rnd.next(1, 100);
        }
        if (rnd.next(0, 1)) {
            for (int& x : a) {
                x = max(4, x);
            }
        }
    }

    shuffle(a.begin(), a.end());
    printCase(n, a);
    return 0;
}
