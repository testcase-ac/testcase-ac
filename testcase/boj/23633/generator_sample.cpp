#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int clampValue(int x, int lo, int hi) {
    if (x < lo) return lo;
    if (x > hi) return hi;
    return x;
}

pair<int, int> makeCase(int mode) {
    int a, b;

    if (mode == 0) {
        a = rnd.next(1, 8);
        b = rnd.next(a, 20);
    } else if (mode == 1) {
        a = rnd.next(1, 60);
        b = rnd.next(a, min(2000, a + rnd.next(0, 80)));
    } else if (mode == 2) {
        b = rnd.any(vector<int>{2, 3, 5, 7, 11, 13, 17, 19, 29, 31, 97, 101,
                                997, 1009, 1997, 1999});
        b = clampValue(b + rnd.next(-2, 2), 1, 2000);
        a = rnd.next(1, b);
    } else if (mode == 3) {
        b = rnd.next(1800, 2000);
        a = rnd.next(max(1, b - rnd.next(0, 120)), b);
    } else {
        a = rnd.next(1, 2000);
        b = rnd.next(a, 2000);
    }

    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = (i < 5 ? i : rnd.next(0, 4));
        cases.push_back(makeCase(mode));
    }

    shuffle(cases.begin(), cases.end());

    println(t);
    for (auto [a, b] : cases) {
        println(a, b);
    }

    return 0;
}
