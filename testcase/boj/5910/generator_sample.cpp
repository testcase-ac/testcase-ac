#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<pair<int, int>> cows;

    auto addCow = [&](int up, int down) {
        cows.push_back({up, down});
    };

    if (mode == 0) {
        n = rnd.next(1, 12);
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, 80);
        for (int i = 0; i < n; ++i) {
            addCow(rnd.next(lo, hi), rnd.next(lo, hi));
        }
    } else if (mode == 1) {
        n = rnd.next(2, 16);
        for (int i = 0; i < n; ++i) {
            addCow(rnd.next(1, 20), rnd.next(100, 50000));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 16);
        for (int i = 0; i < n; ++i) {
            addCow(rnd.next(100, 50000), rnd.next(1, 20));
        }
    } else if (mode == 3) {
        n = rnd.next(4, 18);
        int pivot = rnd.next(10, 1000);
        for (int i = 0; i < n; ++i) {
            int delta = rnd.next(0, min(9, pivot - 1));
            if (i % 3 == 0) {
                addCow(pivot, pivot);
            } else if (i % 3 == 1) {
                addCow(pivot - delta, pivot + delta);
            } else {
                addCow(pivot + delta, pivot - delta);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 14);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                addCow(rnd.next(1, 3), rnd.next(40000, 50000));
            } else {
                addCow(rnd.next(40000, 50000), rnd.next(1, 3));
            }
        }
    } else {
        n = rnd.next(6, 18);
        int base = rnd.next(1, 200);
        for (int i = 0; i < n; ++i) {
            int spread = rnd.next(0, 30);
            addCow(base + i * rnd.next(1, 5), base + spread);
        }
    }

    shuffle(cows.begin(), cows.end());

    println((int)cows.size());
    for (auto [up, down] : cows) {
        println(up, down);
    }

    return 0;
}
