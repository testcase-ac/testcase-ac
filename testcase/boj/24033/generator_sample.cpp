#include "testlib.h"
#include <algorithm>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

int randomPosition(int l, int r) {
    (void)l;
    return rnd.next(1, r);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 18);
    int l, r;

    if (mode == 0) {
        l = rnd.next(1, 6);
        r = rnd.next(1, 6);
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        l = r = rnd.next(1, 20);
    } else if (mode == 2) {
        int base = rnd.next(1, 10);
        int mul = rnd.next(2, 8);
        if (rnd.next(2) == 0) {
            l = base;
            r = base * mul;
        } else {
            l = base * mul;
            r = base;
        }
    } else if (mode == 3) {
        int base = rnd.next(2, 25);
        int mul = rnd.next(2, 20);
        l = base;
        r = base * mul;
    } else if (mode == 4) {
        int base = rnd.next(1, 1000000);
        int mul = rnd.next(1, 1000);
        if (rnd.next(2) == 0) {
            l = base;
            r = base * mul;
        } else {
            l = base * mul;
            r = base;
        }
        n = rnd.next(2, 10);
    } else {
        int base = rnd.next(1, 30);
        int mul = rnd.next(1, 8);
        if (rnd.next(2) == 0) {
            l = base;
            r = base * mul;
        } else {
            l = base * mul;
            r = base;
        }
        n = rnd.next(10, 24);
    }
    n = min(n, r);

    vector<tuple<int, int, int>> particles;
    particles.reserve(n);
    set<int> usedPositions;

    for (int i = 0; i < n; ++i) {
        int x;
        if (mode == 0 && i < 4) {
            vector<int> boundary;
            boundary.push_back(1);
            boundary.push_back(r);
            x = boundary[i % boundary.size()];
        } else {
            x = randomPosition(l, r);
        }
        if (usedPositions.count(x)) {
            if (r <= 1000) {
                vector<int> candidates;
                for (int pos = 1; pos <= r; ++pos) {
                    if (!usedPositions.count(pos)) {
                        candidates.push_back(pos);
                    }
                }
                x = rnd.any(candidates);
            } else {
                while (usedPositions.count(x)) {
                    x = randomPosition(l, r);
                }
            }
        }
        usedPositions.insert(x);

        int d;
        if (mode == 5) {
            d = (i % 2 == 0 ? 1 : -1);
        } else {
            d = rnd.next(2) == 0 ? -1 : 1;
        }

        int w;
        if (i % 7 == 0) {
            w = rnd.next(1, 1000000000);
        } else {
            w = rnd.next(1, 1000);
        }
        particles.emplace_back(x, d, w);
    }

    shuffle(particles.begin(), particles.end());

    println(n, l, r);
    for (const auto& [x, d, w] : particles) {
        println(x, d, w);
    }

    return 0;
}
