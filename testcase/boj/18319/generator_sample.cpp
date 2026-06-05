#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;
    vector<int> berries;

    if (mode == 0) {
        n = rnd.next(1, 5);
        k = 2 * rnd.next(1, 5);
        berries.resize(n);
        for (int& b : berries) b = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = 2 * rnd.next(1, 10);
        int value = rnd.next(1, 80);
        berries.assign(n, value);
        int tweaks = rnd.next(0, n);
        for (int i = 0; i < tweaks; ++i) {
            int idx = rnd.next(0, n - 1);
            berries[idx] = max(1, min(1000, berries[idx] + rnd.next(-5, 5)));
        }
    } else if (mode == 2) {
        n = rnd.next(3, 14);
        k = 2 * rnd.next(1, 12);
        int base = rnd.next(2, 40);
        berries.resize(n);
        for (int& b : berries) {
            int whole = rnd.next(0, 8);
            int rem = rnd.next(0, base - 1);
            b = max(1, min(1000, whole * base + rem));
        }
    } else if (mode == 3) {
        n = rnd.next(4, 15);
        k = 2 * rnd.next(1, 20);
        berries.resize(n);
        for (int& b : berries) {
            b = (rnd.next(0, 3) == 0) ? rnd.next(1, 4) : rnd.next(80, 200);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 12);
        k = 2 * rnd.next(1, 500);
        berries.resize(n);
        for (int& b : berries) {
            b = rnd.next(0, 1) ? rnd.next(950, 1000) : rnd.next(1, 30);
        }
    } else {
        n = rnd.next(10, 25);
        k = 2 * rnd.next(1, 25);
        berries.resize(n);
        int cap = rnd.next(20, 120);
        for (int& b : berries) b = rnd.next(1, cap);
        shuffle(berries.begin(), berries.end());
    }

    println(n, k);
    println(berries);
    return 0;
}
