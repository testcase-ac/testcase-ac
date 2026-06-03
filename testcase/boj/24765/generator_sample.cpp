#include "testlib.h"
#include <utility>
#include <vector>

using namespace std;

pair<int, int> rollOfKind(int kind) {
    if (kind == 0) {
        return rnd.next(0, 1) == 0 ? make_pair(1, 2) : make_pair(2, 1);
    }

    if (kind == 1) {
        int x = rnd.next(1, 6);
        return {x, x};
    }

    while (true) {
        int a = rnd.next(1, 6);
        int b = rnd.next(1, 6);
        if (a == b) continue;
        if ((a == 1 && b == 2) || (a == 2 && b == 1)) continue;
        return {a, b};
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(1, 20);
    vector<pair<pair<int, int>, pair<int, int>>> tests;
    tests.reserve(cases);

    for (int i = 0; i < cases; ++i) {
        int mode = rnd.next(0, 6);
        pair<int, int> left;
        pair<int, int> right;

        if (mode == 0) {
            left = rollOfKind(0);
            right = rollOfKind(rnd.next(1, 2));
        } else if (mode == 1) {
            left = rollOfKind(1);
            right = rollOfKind(1);
        } else if (mode == 2) {
            left = rollOfKind(2);
            right = rollOfKind(2);
        } else if (mode == 3) {
            left = rollOfKind(rnd.next(0, 2));
            right = left;
            if (rnd.next(0, 1) == 1) swap(right.first, right.second);
        } else if (mode == 4) {
            left = rollOfKind(2);
            right = left;
            swap(right.first, right.second);
        } else if (mode == 5) {
            int x = rnd.next(1, 6);
            int y = rnd.next(1, 6);
            left = {x, y};
            right = rollOfKind(rnd.next(0, 2));
        } else {
            left = rollOfKind(rnd.next(0, 2));
            right = rollOfKind(rnd.next(0, 2));
        }

        tests.push_back({left, right});
    }

    for (const auto& test : tests) {
        println(test.first.first, test.first.second, test.second.first, test.second.second);
    }
    println(0, 0, 0, 0);

    return 0;
}
