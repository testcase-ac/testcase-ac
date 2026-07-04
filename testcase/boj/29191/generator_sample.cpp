#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int randomNonZero() {
    int x = rnd.next(-100, 100);
    while (x == 0) x = rnd.next(-100, 100);
    return x;
}

void fillRandom(vector<int>& a, int lo, int hi) {
    for (int& x : a) x = rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(2, 14);
    if (mode == 7) n = rnd.next(40, 80);

    vector<int> a(n);
    if (mode == 0) {
        fillRandom(a, -5, 5);
    } else if (mode == 1) {
        fillRandom(a, -100, 100);
    } else if (mode == 2) {
        fillRandom(a, 1, 100);
    } else if (mode == 3) {
        fillRandom(a, -100, -1);
    } else if (mode == 4) {
        fillRandom(a, -3, 3);
        int zeros = rnd.next(1, n);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < zeros; ++i) a[pos[i]] = 0;
    } else if (mode == 5) {
        fillRandom(a, -2, 2);
        for (int& x : a) {
            if (x == 0 && rnd.next(0, 2) != 0) x = rnd.next(0, 1) ? 1 : -1;
        }
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(vector<int>{-100, -10, -1, 0, 1, 10, 100});
        }
    } else {
        fillRandom(a, -1, 1);
        int spikes = rnd.next(1, min(8, n));
        for (int i = 0; i < spikes; ++i) a[rnd.next(0, n - 1)] = randomNonZero();
    }

    if (rnd.next(0, 3) == 0) {
        a[rnd.next(0, n - 1)] = rnd.any(vector<int>{-100, -1, 0, 1, 100});
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
