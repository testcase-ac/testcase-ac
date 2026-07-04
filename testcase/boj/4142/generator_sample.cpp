#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct TestCase {
    int c;
    int t;
    int l;
    vector<vector<pair<int, int>>> classes;
};

static vector<int> choosePositions(int t, int l, int mode) {
    vector<int> positions;

    if (l <= 5000 && t * 3 >= l) {
        for (int p = 0; p <= l; ++p) positions.push_back(p);
        shuffle(positions.begin(), positions.end());
        positions.resize(t);
        return positions;
    }

    if (mode == 0) {
        positions.push_back(0);
        if (l > 0) positions.push_back(l);
    } else if (mode == 1) {
        int center = rnd.next(0, l);
        int radius = max(1, min(l + 1, rnd.next(1, 12)));
        for (int delta = -radius; delta <= radius; ++delta) {
            int p = center + delta;
            if (0 <= p && p <= l) positions.push_back(p);
        }
    } else {
        int step = max(1, l / max(1, t - 1));
        for (int p = 0; p <= l && (int)positions.size() < t * 2; p += step) {
            positions.push_back(p);
        }
        positions.push_back(l);
    }

    int stride = rnd.next(1, max(1, l));
    int start = rnd.next(0, l);
    for (int k = 0; (int)positions.size() < t * 2 && k <= l; ++k) {
        positions.push_back((start + 1LL * k * stride) % (l + 1));
    }

    sort(positions.begin(), positions.end());
    positions.erase(unique(positions.begin(), positions.end()), positions.end());

    while ((int)positions.size() < t) positions.push_back(rnd.next(0, l));
    sort(positions.begin(), positions.end());
    positions.erase(unique(positions.begin(), positions.end()), positions.end());

    while ((int)positions.size() < t) {
        int p = rnd.next(0, l);
        if (!binary_search(positions.begin(), positions.end(), p)) {
            positions.insert(lower_bound(positions.begin(), positions.end(), p), p);
        }
    }

    shuffle(positions.begin(), positions.end());
    positions.resize(t);
    return positions;
}

static int chooseEnergy(int category, int classIndex, int mode) {
    if (mode == 0) return rnd.next(1, 15);
    if (mode == 1) return rnd.any(vector<int>{1, 2, 999999, 1000000});
    if (mode == 2) return 1 + ((category * 37 + classIndex * 101 + rnd.next(0, 50)) % 1000);
    return rnd.next(1, 1000000);
}

static TestCase makeCase(int c, int t, int l, int mode) {
    TestCase tc;
    tc.c = c;
    tc.t = t;
    tc.l = max(l, t - 1);
    tc.classes.resize(c);

    for (int i = 0; i < c; ++i) {
        vector<int> positions = choosePositions(t, tc.l, (mode + i) % 3);
        if (mode == 3 && i % 2 == 1) reverse(positions.begin(), positions.end());
        for (int j = 0; j < t; ++j) {
            tc.classes[i].push_back({positions[j], chooseEnergy(i + 1, j + 1, mode)});
        }
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<TestCase> tests;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        tests.push_back(makeCase(1, rnd.next(1, 6), rnd.next(1, 20), 0));
        tests.push_back(makeCase(rnd.next(2, 5), rnd.next(1, 5), rnd.next(5, 40), 1));
    } else if (mode == 1) {
        tests.push_back(makeCase(rnd.next(2, 8), rnd.next(2, 8), rnd.next(8, 60), 2));
        tests.push_back(makeCase(rnd.next(3, 10), rnd.next(2, 6), rnd.next(10, 100), 3));
    } else if (mode == 2) {
        tests.push_back(makeCase(25, rnd.next(2, 12), rnd.next(30, 200), 1));
    } else if (mode == 3) {
        int t = rnd.next(50, 180);
        tests.push_back(makeCase(rnd.next(2, 5), t, rnd.next(t, 1000000), 2));
    } else if (mode == 4) {
        int z = rnd.next(8, 20);
        int total = 0;
        for (int i = 0; i < z; ++i) {
            int c = rnd.next(1, 6);
            int t = rnd.next(1, min(20, (25000 - total) / c));
            total += c * t;
            tests.push_back(makeCase(c, t, rnd.next(max(1, t - 1), 500), i % 4));
        }
    } else {
        int c = rnd.next(10, 25);
        int t = rnd.next(10, min(1000, 25000 / c));
        tests.push_back(makeCase(c, t, rnd.next(t, 1000000), 3));
    }

    println((int)tests.size());
    for (const TestCase &tc : tests) {
        println(tc.c, tc.t, tc.l);
        for (const auto &category : tc.classes) {
            for (auto cls : category) println(cls.first, cls.second);
        }
    }

    return 0;
}
