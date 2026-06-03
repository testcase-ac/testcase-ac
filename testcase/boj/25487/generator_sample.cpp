#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 25);
    vector<array<int, 3>> cases;
    cases.reserve(t);

    auto addCase = [&](int a, int b, int c) {
        cases.push_back({a, b, c});
    };

    addCase(1, 1, 1);
    addCase(100000, 100000, 100000);

    while ((int)cases.size() < t) {
        int mode = rnd.next(0, 7);
        int a, b, c;

        if (mode == 0) {
            int v = rnd.next(1, 40);
            a = b = c = v;
        } else if (mode == 1) {
            int lo = rnd.next(1, 20);
            int hi = rnd.next(lo, 100);
            a = lo;
            b = rnd.next(lo, hi);
            c = hi;
        } else if (mode == 2) {
            int m = rnd.next(1, 100);
            a = rnd.next(m, 100000);
            b = m;
            c = rnd.next(m, 100000);
        } else if (mode == 3) {
            int m = rnd.next(1, 1000);
            a = rnd.next(m, 100000);
            b = rnd.next(m, 100000);
            c = m;
        } else if (mode == 4) {
            a = rnd.any(vector<int>{1, 2, 99999, 100000});
            b = rnd.next(1, 100000);
            c = rnd.next(1, 100000);
        } else if (mode == 5) {
            int base = rnd.next(99950, 100000);
            a = rnd.next(base, 100000);
            b = rnd.next(base, 100000);
            c = rnd.next(base, 100000);
        } else {
            a = rnd.next(1, 100000);
            b = rnd.next(1, 100000);
            c = rnd.next(1, 100000);
        }

        if (rnd.next(2)) {
            array<int, 3> values = {a, b, c};
            shuffle(values.begin(), values.end());
            a = values[0];
            b = values[1];
            c = values[2];
        }

        addCase(a, b, c);
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto cur : cases) {
        println(cur[0], cur[1], cur[2]);
    }

    return 0;
}
