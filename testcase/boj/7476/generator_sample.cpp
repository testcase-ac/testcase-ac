#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {
constexpr long long kMinValue = -(1LL << 31);
constexpr long long kMaxValue = (1LL << 31) - 1;

void printSequence(const vector<long long>& values) {
    println(static_cast<int>(values.size()));
    for (int i = 0; i < static_cast<int>(values.size()); ++i) {
        if (i > 0) printf(" ");
        printf("%lld", values[i]);
    }
    printf("\n");
}

long long edgeOrSmallValue() {
    if (rnd.next(10) == 0) return rnd.next(2) == 0 ? kMinValue : kMaxValue;
    return rnd.next(-30, 30);
}

void addNoise(vector<long long>& values, int count, int lo, int hi) {
    for (int i = 0; i < count; ++i) values.push_back(rnd.next(lo, hi));
}

vector<long long> plantedIncreasing(int len, int start, int gap) {
    vector<long long> values;
    for (int i = 0; i < len; ++i) values.push_back(start + 1LL * i * gap);
    return values;
}
}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> a;
    vector<long long> b;
    int mode = rnd.next(6);

    if (mode == 0) {
        int n = rnd.next(1, 25);
        int m = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(-40, -1));
        for (int i = 0; i < m; ++i) b.push_back(rnd.next(1, 40));
    } else if (mode == 1) {
        int n = rnd.next(1, 35);
        int m = rnd.next(1, 35);
        int lo = rnd.next(-8, 0);
        int hi = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(lo, hi));
        for (int i = 0; i < m; ++i) b.push_back(rnd.next(lo, hi));
    } else if (mode == 2) {
        int len = rnd.next(2, 20);
        vector<long long> base = plantedIncreasing(len, rnd.next(-25, -5), rnd.next(1, 4));
        a = base;
        b = base;
        reverse(b.begin(), b.end());
        addNoise(a, rnd.next(0, 8), -30, 30);
        addNoise(b, rnd.next(0, 8), -30, 30);
    } else if (mode == 3) {
        int len = rnd.next(1, 18);
        vector<long long> common = plantedIncreasing(len, rnd.next(-50, -10), rnd.next(2, 6));
        addNoise(a, rnd.next(0, 10), -60, 60);
        for (long long x : common) {
            a.push_back(x);
            if (rnd.next(2)) a.push_back(rnd.next(-60, 60));
        }
        addNoise(b, rnd.next(0, 10), -60, 60);
        for (long long x : common) {
            if (rnd.next(2)) b.push_back(rnd.next(-60, 60));
            b.push_back(x);
        }
        addNoise(a, rnd.next(0, 10), -60, 60);
        addNoise(b, rnd.next(0, 10), -60, 60);
    } else if (mode == 4) {
        int n = rnd.next(1, 45);
        int m = rnd.next(1, 45);
        for (int i = 0; i < n; ++i) a.push_back(edgeOrSmallValue());
        for (int i = 0; i < m; ++i) b.push_back(edgeOrSmallValue());
    } else {
        int len = rnd.next(30, 80);
        int window = rnd.next(5, 17);
        for (int i = 0; i < len; ++i) a.push_back(rnd.next(-window, window));
        for (int i = 0; i < len; ++i) b.push_back(rnd.next(-window, window));
    }

    if (mode == 0 || mode == 1 || mode == 4 || mode == 5) {
        shuffle(a.begin(), a.end());
        shuffle(b.begin(), b.end());
    }

    printSequence(a);
    printSequence(b);

    return 0;
}
