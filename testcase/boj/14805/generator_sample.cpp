#include "testlib.h"
#include <algorithm>
#include <array>
#include <vector>
using namespace std;

struct CaseCounts {
    int n;
    int r;
    int y;
    int b;
};

static CaseCounts makeBalancedCase(int n) {
    int r = n / 3;
    int y = (n - r) / 2;
    int b = n - r - y;
    array<int, 3> values = {r, y, b};
    shuffle(values.begin(), values.end());
    return {n, values[0], values[1], values[2]};
}

static CaseCounts makeDominantCase(int n) {
    int dominant = rnd.next(n / 2 + 1, n);
    int rest = n - dominant;
    int first = rnd.next(0, rest);
    array<int, 3> values = {dominant, first, rest - first};
    shuffle(values.begin(), values.end());
    return {n, values[0], values[1], values[2]};
}

static CaseCounts makeTightCase(int n) {
    int largest = n / 2;
    int rest = n - largest;
    int first = rnd.next(0, rest);
    array<int, 3> values = {largest, first, rest - first};
    shuffle(values.begin(), values.end());
    return {n, values[0], values[1], values[2]};
}

static CaseCounts makeSparseColorCase(int n) {
    int lone = rnd.next(0, 2);
    int small = rnd.next(0, min(2, n - 3));
    int rest = n - small;
    int first = rnd.next(0, rest);
    array<int, 3> values = {first, rest - first, small};
    rotate(values.begin(), values.begin() + (2 - lone), values.end());
    return {n, values[0], values[1], values[2]};
}

static CaseCounts makeRandomCase(int n) {
    int r = rnd.next(0, n);
    int y = rnd.next(0, n - r);
    int b = n - r - y;
    array<int, 3> values = {r, y, b};
    shuffle(values.begin(), values.end());
    return {n, values[0], values[1], values[2]};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 18);
    vector<CaseCounts> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 4);
        int n;
        if (i == 0) {
            n = 3;
        } else if (i == 1) {
            n = rnd.next(4, 8);
        } else if (rnd.next(0, 9) == 0) {
            n = rnd.next(30, 80);
        } else {
            n = rnd.next(3, 20);
        }

        if (mode == 0) {
            cases.push_back(makeBalancedCase(n));
        } else if (mode == 1 && n >= 4) {
            cases.push_back(makeDominantCase(n));
        } else if (mode == 2 && n >= 4) {
            cases.push_back(makeTightCase(n));
        } else if (mode == 3 && n >= 5) {
            cases.push_back(makeSparseColorCase(n));
        } else {
            cases.push_back(makeRandomCase(n));
        }
    }

    println((int)cases.size());
    for (const CaseCounts& c : cases) {
        println(c.n, c.r, 0, c.y, 0, c.b, 0);
    }

    return 0;
}
