#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> makeCase(int mode) {
    if (mode == 0) {
        return {1, 1};
    }
    if (mode == 1) {
        return {1, rnd.next(2, 100)};
    }
    if (mode == 2) {
        return {rnd.next(2, 100), 1};
    }
    if (mode == 3) {
        int side = rnd.next(2, 12);
        return {side, side};
    }
    if (mode == 4) {
        int shortSide = rnd.next(2, 8);
        int longSide = rnd.next(9, 30);
        if (rnd.next(0, 1)) swap(shortSide, longSide);
        return {shortSide, longSide};
    }
    if (mode == 5) {
        int n = rnd.any(vector<int>{2, 3, 4, 99, 100});
        int m = rnd.any(vector<int>{2, 3, 4, 99, 100});
        return {n, m};
    }
    return {rnd.next(1, 100), rnd.next(1, 100)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 30);
    vector<pair<int, int>> cases;
    cases.reserve(t);

    cases.push_back({1, 1});
    cases.push_back({1, rnd.next(2, 100)});
    cases.push_back({rnd.next(2, 100), 1});
    cases.push_back({2, 2});
    cases.push_back({100, 100});

    while ((int)cases.size() < t) {
        cases.push_back(makeCase(rnd.next(0, 6)));
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [n, m] : cases) {
        println(n, m);
    }

    return 0;
}
