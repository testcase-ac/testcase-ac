#include "testlib.h"

#include <cstdint>
#include <set>
#include <vector>

using namespace std;

using int64 = long long;

const int64 LIMIT = 1000000000000LL;

int64 clampCoord(int64 x) {
    if (x < -LIMIT) return -LIMIT;
    if (x > LIMIT) return LIMIT;
    return x;
}

vector<int64> randomPoint(int n, int mode, int index) {
    vector<int64> p(n);
    for (int j = 0; j < n; ++j) {
        if (mode == 0) {
            p[j] = rnd.next(-20, 20);
        } else if (mode == 1) {
            int64 base = (j % 2 == 0 ? LIMIT - 200 : -LIMIT + 200);
            p[j] = clampCoord(base + rnd.next(-50, 50));
        } else if (mode == 2) {
            p[j] = (rnd.next(0, 3) - 1) * rnd.next(0, 100);
        } else if (mode == 3) {
            p[j] = (j == index % n ? rnd.next(-1000, 1000) : rnd.next(-3, 3));
        } else {
            int64 base = (int64)(index - 6) * rnd.next(1, 17);
            p[j] = base + rnd.next(-5, 5) + (j % 3 - 1) * rnd.next(0, 9);
        }
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int m;
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 15);
    } else if (mode == 1) {
        n = rnd.next(2, 6);
        m = rnd.next(2, 12);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
        m = rnd.next(2, 9);
    } else if (mode == 3) {
        n = rnd.next(2, 8);
        m = rnd.next(7, 15);
        if (m % 2 == 0) --m;
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        m = rnd.next(2, 14);
        if (m % 2 == 1) ++m;
    } else {
        n = rnd.next(1, 8);
        m = rnd.next(1, 16);
    }

    set<vector<int64>> seen;
    vector<vector<int64>> points;
    while ((int)points.size() < m) {
        int idx = (int)points.size();
        vector<int64> p = randomPoint(n, mode, idx);
        for (int attempt = 0; !seen.insert(p).second; ++attempt) {
            p[idx % n] = -LIMIT + (int64)(idx + 1) * 1000000 + attempt;
        }
        points.push_back(p);
    }

    if (rnd.next(0, 1)) {
        shuffle(points.begin(), points.end());
    }

    println(n, m);
    for (const auto& p : points) {
        println(p);
    }

    return 0;
}
