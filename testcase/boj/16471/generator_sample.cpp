#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int boundedValue(int x) {
    return max(0, min(100000, x));
}

void shuffleCards(vector<int>& cards) {
    shuffle(cards.begin(), cards.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 5) {
        n = 2 * rnd.next(20, 80) + 1;
    } else {
        n = 2 * rnd.next(0, 12) + 1;
    }

    vector<int> juwon(n), boss(n);
    int pivot = rnd.next(2, 99998);

    if (mode == 0) {
        int lo = rnd.next(0, 99990);
        int hi = rnd.next(lo, min(100000, lo + rnd.next(0, 20)));
        for (int i = 0; i < n; ++i) {
            juwon[i] = rnd.next(lo, hi);
            boss[i] = rnd.next(lo, hi);
        }
    } else if (mode == 1) {
        int base = rnd.next(1, 99999);
        int need = (n + 1) / 2;
        for (int i = 0; i < n; ++i) {
            juwon[i] = base;
            boss[i] = base;
        }
        for (int i = 0; i < need; ++i) {
            juwon[i] = boundedValue(base - rnd.next(1, 3));
            boss[i] = boundedValue(base + rnd.next(1, 3));
        }
    } else if (mode == 2) {
        int base = rnd.next(1, 99999);
        int need = max(0, (n - 1) / 2);
        for (int i = 0; i < n; ++i) {
            juwon[i] = base;
            boss[i] = base;
        }
        for (int i = 0; i < need; ++i) {
            juwon[i] = boundedValue(base - rnd.next(1, 3));
            boss[i] = boundedValue(base + rnd.next(1, 3));
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            juwon[i] = boundedValue(pivot + rnd.next(-2, 2));
            boss[i] = boundedValue(pivot + rnd.next(-2, 2));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            juwon[i] = rnd.any(vector<int>{0, 1, 99999, 100000});
            boss[i] = rnd.any(vector<int>{0, 1, 99999, 100000});
        }
    } else {
        int spread = rnd.next(3, 200);
        for (int i = 0; i < n; ++i) {
            int rank = rnd.next(0, spread);
            juwon[i] = boundedValue(pivot - spread / 2 + rank);
            boss[i] = boundedValue(pivot - spread / 2 + rnd.next(0, spread));
        }
        sort(juwon.begin(), juwon.end());
        sort(boss.begin(), boss.end());
    }

    shuffleCards(juwon);
    shuffleCards(boss);

    println(n);
    println(juwon);
    println(boss);
    return 0;
}
