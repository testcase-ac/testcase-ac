#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> makeCase(int mode) {
    int a;
    int k;

    if (mode == 0) {
        a = rnd.next(3, 30);
        k = rnd.next(2, a - 1);
    } else if (mode == 1) {
        a = rnd.next(3, 120);
        k = rnd.next(2, min(a - 1, 8));
    } else if (mode == 2) {
        a = rnd.next(20, 300);
        k = rnd.next(max(2, a - 12), a - 1);
    } else if (mode == 3) {
        a = rnd.next(90000, 100000);
        k = rnd.next(2, 30);
    } else if (mode == 4) {
        a = rnd.next(90000, 100000);
        k = rnd.next(a / 3, a - 1);
    } else if (mode == 5) {
        a = rnd.next(500, 5000);
        k = rnd.next(10, min(a - 1, 250));
    } else {
        vector<int> anchors = {12, 30, 100, 210, 1000, 99991, 100000};
        a = rnd.any(anchors);
        k = rnd.next(2, min(a - 1, max(2, a / rnd.next(2, 12))));
    }

    return {a, k};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 20);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    for (int mode = 0; mode < 7 && (int)cases.size() < t; ++mode) {
        cases.push_back(makeCase(mode));
    }
    while ((int)cases.size() < t) {
        cases.push_back(makeCase(rnd.next(0, 6)));
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [a, k] : cases) {
        println(a, k);
    }

    return 0;
}
