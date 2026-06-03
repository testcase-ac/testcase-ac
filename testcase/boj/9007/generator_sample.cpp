#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>
using namespace std;

constexpr int kMaxK = 40000000;
constexpr int kMaxWeight = 10000000;

int clampWeight(int value) {
    return max(1, min(kMaxWeight, value));
}

vector<int> randomWeights(int n, int lo, int hi) {
    vector<int> values;
    for (int i = 0; i < n; ++i) {
        values.push_back(rnd.next(lo, hi));
    }
    return values;
}

array<vector<int>, 4> makeCase(int mode, int& k, int& n) {
    array<vector<int>, 4> classes;

    if (mode == 0) {
        n = 1;
        if (rnd.next(2) == 0) {
            k = 1;
            for (auto& c : classes) c = {1};
        } else {
            k = kMaxK;
            for (auto& c : classes) c = {kMaxWeight};
        }
        return classes;
    }

    if (mode == 1) {
        n = rnd.next(2, 8);
        int base = rnd.next(1, 20);
        k = 4 * base + rnd.next(-3, 3);
        k = max(1, k);
        for (auto& c : classes) {
            c.assign(n, base);
            for (int& x : c) {
                if (rnd.next(100) < 35) x = clampWeight(base + rnd.next(-2, 2));
            }
            shuffle(c.begin(), c.end());
        }
        return classes;
    }

    if (mode == 2) {
        n = rnd.next(3, 10);
        int target = rnd.next(80, 400);
        k = target;
        int a = rnd.next(1, target / 4);
        int b = rnd.next(1, target / 4);
        int c = rnd.next(1, target / 4);
        int dLow = clampWeight(target - a - b - c - 2);
        int dHigh = clampWeight(target - a - b - c + 2);
        classes[0] = randomWeights(n, 1, max(1, target / 2));
        classes[1] = randomWeights(n, 1, max(1, target / 2));
        classes[2] = randomWeights(n, 1, max(1, target / 2));
        classes[3] = randomWeights(n, 1, max(1, target / 2));
        classes[0][0] = a;
        classes[1][0] = b;
        classes[2][0] = c;
        classes[3][0] = dLow;
        if (n > 1) classes[3][1] = dHigh;
        for (auto& cls : classes) shuffle(cls.begin(), cls.end());
        return classes;
    }

    if (mode == 3) {
        n = rnd.next(4, 12);
        k = rnd.next(1000, 100000);
        int left = rnd.next(2, k - 2);
        int rightLow = max(2, k - left - 1);
        int rightHigh = min(2 * kMaxWeight, k - left + 1);
        int a = rnd.next(1, min(kMaxWeight, left - 1));
        int b = left - a;
        int c = rnd.next(1, min(kMaxWeight, rightLow - 1));
        int d = rightLow - c;
        int e = rnd.next(1, min(kMaxWeight, rightHigh - 1));
        int f = rightHigh - e;

        classes[0] = randomWeights(n, 1, min(kMaxWeight, k));
        classes[1] = randomWeights(n, 1, min(kMaxWeight, k));
        classes[2] = randomWeights(n, 1, min(kMaxWeight, k));
        classes[3] = randomWeights(n, 1, min(kMaxWeight, k));
        classes[0][0] = clampWeight(a);
        classes[1][0] = clampWeight(b);
        classes[2][0] = clampWeight(c);
        classes[3][0] = clampWeight(d);
        classes[2][1] = clampWeight(e);
        classes[3][1] = clampWeight(f);
        for (auto& cls : classes) shuffle(cls.begin(), cls.end());
        return classes;
    }

    n = rnd.next(5, 25);
    int band = rnd.any(vector<int>{20, 1000, 100000, kMaxWeight});
    k = rnd.next(1, kMaxK);
    for (auto& c : classes) {
        int lo = rnd.next(1, max(1, band / 2));
        int hi = rnd.next(lo, band);
        c = randomWeights(n, lo, hi);
        shuffle(c.begin(), c.end());
    }
    return classes;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int k;
        int n;
        auto classes = makeCase(tc % 5, k, n);

        println(k, n);
        for (const auto& c : classes) {
            println(c);
        }
    }

    return 0;
}
