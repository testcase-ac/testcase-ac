#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 18);
    int l = rnd.next(max(20, n + 2), 180);
    int p = rnd.next(1, min(l + 80, 250));

    vector<pair<int, int>> stops;
    set<int> used;

    auto addStop = [&](int a, int b) {
        a = max(1, min(a, l - 1));
        if (used.insert(a).second) {
            stops.push_back({a, max(1, min(b, 100))});
        }
    };

    if (mode == 0) {
        p = rnd.next(l, l + 80);
    } else if (mode == 1) {
        p = rnd.next(1, max(1, l / 4));
        int farGapStart = rnd.next(p + 2, l - 1);
        for (int a = 1; a < farGapStart && (int)stops.size() < n; ++a) {
            if (rnd.next(0, 2) == 0) addStop(a, rnd.next(1, 3));
        }
        addStop(farGapStart, rnd.next(1, 100));
    } else if (mode == 2) {
        int step = rnd.next(3, 12);
        p = rnd.next(step, step + 5);
        for (int a = rnd.next(1, step); a < l && (int)stops.size() < n; a += rnd.next(1, step)) {
            addStop(a, rnd.next(1, 100));
        }
    } else if (mode == 3) {
        int center = rnd.next(2, l - 1);
        p = rnd.next(1, min(l, 80));
        for (int i = 0; i < n; ++i) {
            addStop(center + rnd.next(-8, 8), rnd.next(1, 100));
        }
    } else {
        p = rnd.next(1, min(l, 100));
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(1, l - 1);
            int b = rnd.next(0, 3) == 0 ? 100 : rnd.next(1, 25);
            addStop(a, b);
        }
    }

    while ((int)stops.size() < n) {
        addStop(rnd.next(1, l - 1), rnd.next(1, 100));
    }

    shuffle(stops.begin(), stops.end());

    println((int)stops.size());
    for (auto [a, b] : stops) println(a, b);
    println(l, p);

    return 0;
}
