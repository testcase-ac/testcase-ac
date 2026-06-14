#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int m;
    vector<int> x;

    if (mode == 0) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 12);
        x.assign(n, 1);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        m = n;
        x.resize(n);
        int high = rnd.next(30, 300);
        for (int i = 0; i < n; ++i) x[i] = rnd.next(1, high);
        x[rnd.next(n)] = 125000000;
    } else if (mode == 2) {
        n = rnd.next(6, 30);
        m = rnd.next(2, 10);
        x.resize(n);
        for (int i = 0; i < n; ++i) {
            x[i] = (i % m == m - 1) ? rnd.next(1, 4) : rnd.next(5, 30);
        }
    } else if (mode == 3) {
        m = rnd.next(2, 20);
        int k = rnd.next(2, 8);
        n = m * k;
        x.resize(n);
        for (int i = 0; i < n; ++i) x[i] = rnd.next(1, 40);
    } else if (mode == 4) {
        n = rnd.next(2, 40);
        m = 500;
        x.resize(n);
        for (int i = 0; i < n; ++i) x[i] = rnd.next(1, 1000);
    } else if (mode == 5) {
        n = rnd.next(50, 140);
        m = rnd.next(2, 500);
        x.resize(n);
        int base = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) x[i] = base + rnd.next(0, 3);
    } else if (mode == 6) {
        n = rnd.next(2, 60);
        m = rnd.next(2, 500);
        x.resize(n);
        for (int i = 0; i < n; ++i) {
            x[i] = (rnd.next(0, 4) == 0) ? 125000000 : rnd.next(1, 10000);
        }
    } else {
        n = rnd.next(2, 200);
        m = rnd.next(2, 500);
        x.resize(n);
        int upper = rnd.next(1, 125000000);
        for (int i = 0; i < n; ++i) x[i] = rnd.next(1, upper);
    }

    println(n, m);
    println(x);

    return 0;
}
