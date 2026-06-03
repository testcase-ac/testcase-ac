#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int randomNodeAtDepth(int depth) {
    int lo = 1 << depth;
    int hi = (1 << (depth + 1)) - 1;
    return rnd.next(lo, hi);
}

int ancestorOf(int node, int steps) {
    while (steps-- > 0) node /= 2;
    return node;
}

pair<int, int> makePair(int mode) {
    int a = 1;
    int b = 2;

    if (mode == 0) {
        a = rnd.next(1, 12);
        b = rnd.next(1, 12);
    } else if (mode == 1) {
        int depth = rnd.next(1, 9);
        a = randomNodeAtDepth(depth);
        b = ancestorOf(a, rnd.next(1, depth));
    } else if (mode == 2) {
        int parent = rnd.next(1, 511);
        a = parent * 2;
        b = parent * 2 + 1;
    } else if (mode == 3) {
        a = rnd.next(900, 1023);
        b = rnd.next(900, 1023);
    } else if (mode == 4) {
        int top = rnd.next(1, 31);
        int left = top;
        int right = top;
        while (left * 2 <= 1023) left = left * 2 + rnd.next(0, 1);
        while (right * 2 <= 1023) right = right * 2 + rnd.next(0, 1);
        a = left;
        b = right;
    } else {
        a = rnd.next(1, 1023);
        b = rnd.next(1, 1023);
    }

    while (a == b) b = rnd.next(1, 1023);
    if (rnd.next(0, 1)) swap(a, b);
    return {a, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 40);
    vector<pair<int, int>> tests;
    tests.reserve(t);

    tests.push_back({1, 2});
    tests.push_back({1022, 1023});
    tests.push_back({512, 1023});

    while ((int)tests.size() < t) {
        tests.push_back(makePair(rnd.next(0, 5)));
    }

    shuffle(tests.begin(), tests.end());
    println((int)tests.size());
    for (auto [a, b] : tests) println(a, b);

    return 0;
}
