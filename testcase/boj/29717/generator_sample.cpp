#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 1000000000;

int clampN(long long value) {
    return (int)max(1LL, min((long long)MAX_N, value));
}

int nearTriangularLevel() {
    int level = rnd.next(1, 44720);
    long long threshold = 1LL * level * (level + 1);
    long long lo = max(1LL, threshold / 2 - 5);
    long long hi = min((long long)MAX_N, threshold / 2 + 5);
    return (int)rnd.next(lo, hi);
}

int randomN() {
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        return rnd.next(1, 30);
    }
    if (mode == 1) {
        int base = rnd.next(1, 100000);
        return clampN(1LL * base * base + rnd.next(0, 20) - 10);
    }
    if (mode == 2) {
        return nearTriangularLevel();
    }
    if (mode == 3) {
        return (int)rnd.next(1LL, (long long)MAX_N);
    }
    if (mode == 4) {
        return MAX_N - rnd.next(0, 1000);
    }
    int a = rnd.next(1, 1000);
    int b = rnd.next(1, 1000);
    return a * b;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 30);
    vector<int> values;
    values.reserve(t);

    if (t >= 1) values.push_back(1);
    if (t >= 2) values.push_back(MAX_N);
    if (t >= 3) values.push_back(MAX_N - rnd.next(0, 1000));

    while ((int)values.size() < t) {
        values.push_back(randomN());
    }

    shuffle(values.begin(), values.end());

    println(t);
    for (int value : values) {
        println(value);
    }

    return 0;
}
