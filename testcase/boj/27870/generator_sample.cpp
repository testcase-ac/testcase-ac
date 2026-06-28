#include "testlib.h"

#include <set>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = 1;
    vector<tuple<int, int, int, int>> pairs;
    set<tuple<int, int, int, int>> used;

    auto addPair = [&](int p, int x, int q, int y) {
        if (p > q) {
            swap(p, q);
            swap(x, y);
        }
        if (used.emplace(p, x, q, y).second) {
            pairs.emplace_back(p, x, q, y);
        }
    };

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        int m = rnd.next(1, min(18, 3 * n * n));
        while ((int)pairs.size() < m) {
            int q = rnd.next(2, 4);
            addPair(1, rnd.next(1, n), q, rnd.next(1, n));
        }
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        int center = rnd.next(1, n);
        for (int q = 2; q <= 4; ++q) {
            int cnt = rnd.next(1, min(n, 8));
            for (int i = 0; i < cnt; ++i) {
                addPair(1, center, q, rnd.next(1, n));
            }
        }
        int extras = rnd.next(0, 12);
        for (int i = 0; i < extras; ++i) {
            int q = rnd.next(2, 4);
            addPair(1, rnd.next(1, n), q, rnd.next(1, n));
        }
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        int a = rnd.next(1, n);
        int b = rnd.next(1, n);
        int c = rnd.next(1, n);
        int d = rnd.next(1, n);
        addPair(1, a, 2, b);
        addPair(1, a, 3, c);
        addPair(1, a, 4, d);
        int extras = rnd.next(0, 12);
        for (int i = 0; i < extras; ++i) {
            int q = rnd.next(2, 4);
            addPair(1, rnd.next(1, n), q, rnd.next(1, n));
        }
    } else if (mode == 4) {
        n = rnd.next(3, 8);
        int active = rnd.next(2, min(n, 6));
        for (int q = 2; q <= 4; ++q) {
            for (int x = 1; x <= active; ++x) {
                for (int y = 1; y <= active; ++y) {
                    if (rnd.next(100) < 35) {
                        addPair(1, x, q, y);
                    }
                }
            }
        }
    } else {
        n = rnd.next(6, 8);
        int m = rnd.next(20, min(45, 3 * n * n));
        while ((int)pairs.size() < m) {
            int q = rnd.next(2, 4);
            int lowBias = rnd.next(100) < 70 ? rnd.next(1, min(n, 4)) : rnd.next(1, n);
            int anyItem = rnd.next(1, n);
            addPair(1, lowBias, q, anyItem);
        }
    }

    shuffle(pairs.begin(), pairs.end());

    println(n, (int)pairs.size());
    for (auto [p, x, q, y] : pairs) {
        println(p, x, q, y);
    }

    return 0;
}
