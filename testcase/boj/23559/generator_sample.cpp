#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int tasteNear(int center, int spread) {
    int lo = max(1, center - spread);
    int hi = min(10000, center + spread);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode <= 1) {
        n = rnd.next(1, 3);
    } else if (mode <= 4) {
        n = rnd.next(4, 15);
    } else {
        n = rnd.next(16, 35);
    }

    int canUpgrade;
    if (mode == 0) {
        canUpgrade = 0;
    } else if (mode == 1) {
        canUpgrade = n;
    } else if (mode == 2) {
        canUpgrade = rnd.next(0, min(n, 2));
    } else if (mode == 3) {
        canUpgrade = rnd.next(max(0, n - 2), n);
    } else {
        canUpgrade = rnd.next(0, n);
    }

    int extra = canUpgrade == n ? 0 : rnd.next(0, 3999);
    int x = 1000 * n + 4000 * canUpgrade + extra;

    vector<pair<int, int>> menu(n);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            int b = rnd.next(1, 10000);
            int a = rnd.next(1, b);
            menu[i] = {a, b};
        } else if (mode == 1) {
            int b = rnd.next(1, 7000);
            int a = rnd.next(b, 10000);
            menu[i] = {a, b};
        } else if (mode == 2) {
            int base = rnd.next(20, 9980);
            menu[i] = {tasteNear(base, 8), tasteNear(base, 8)};
        } else if (mode == 3) {
            int b = rnd.next(1, 10000);
            int delta = rnd.next(-500, 500);
            int a = max(1, min(10000, b + delta));
            menu[i] = {a, b};
        } else if (mode == 4) {
            int b = rnd.next(1, 2000);
            int a = rnd.next(8000, 10000);
            if (rnd.next(0, 3) == 0) swap(a, b);
            menu[i] = {a, b};
        } else {
            menu[i] = {rnd.next(1, 10000), rnd.next(1, 10000)};
        }
    }

    shuffle(menu.begin(), menu.end());

    println(n, x);
    for (auto [a, b] : menu) {
        println(a, b);
    }

    return 0;
}
