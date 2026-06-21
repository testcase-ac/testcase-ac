#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(1, 24);
    int n = rnd.next(1, 12);

    vector<int> p(m);
    vector<int> c(n), e(n);

    if (mode == 0) {
        int base = rnd.next(1, 30);
        for (int i = 0; i < m; ++i) p[i] = base + rnd.next(0, 12);
        for (int j = 0; j < n; ++j) {
            c[j] = rnd.next(1, min(8, m + 3));
            e[j] = rnd.next(1, 70);
        }
    } else if (mode == 1) {
        for (int i = 0; i < m; ++i) p[i] = rnd.next(1, 100);
        for (int j = 0; j < n; ++j) {
            c[j] = rnd.next(1, min(5, m));
            e[j] = rnd.next(120, 600);
        }
    } else if (mode == 2) {
        for (int i = 0; i < m; ++i) p[i] = (i % 3 == 0 ? rnd.next(80, 220) : rnd.next(1, 40));
        for (int j = 0; j < n; ++j) {
            c[j] = rnd.next(1, min(10, m + 5));
            e[j] = rnd.next(10, 250);
        }
    } else if (mode == 3) {
        for (int i = 0; i < m; ++i) p[i] = rnd.next(10, 500);
        for (int j = 0; j < n; ++j) {
            c[j] = (j % 2 == 0 ? 1 : rnd.next(2, min(12, m + 6)));
            e[j] = rnd.next(5, 350);
        }
    } else if (mode == 4) {
        m = rnd.next(8, 30);
        n = rnd.next(4, 14);
        p.assign(m, 0);
        c.assign(n, 0);
        e.assign(n, 0);
        for (int i = 0; i < m; ++i) p[i] = rnd.next(1, 10000);
        for (int j = 0; j < n; ++j) {
            c[j] = rnd.next(1, 10000);
            e[j] = rnd.next(1, 10000);
        }
    } else {
        m = rnd.next(1, 10);
        n = rnd.next(1, 8);
        p.assign(m, 0);
        c.assign(n, 0);
        e.assign(n, 0);
        for (int i = 0; i < m; ++i) p[i] = rnd.next(1, 15);
        for (int j = 0; j < n; ++j) {
            c[j] = rnd.next(1, 4);
            e[j] = rnd.next(1, 35);
        }
    }

    shuffle(p.begin(), p.end());
    vector<int> order(n);
    for (int j = 0; j < n; ++j) order[j] = j;
    shuffle(order.begin(), order.end());

    println(m, n);
    for (int price : p) println(price);
    for (int idx : order) println(c[idx], e[idx]);

    return 0;
}
