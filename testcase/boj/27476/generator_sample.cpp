#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {

constexpr long long kMinAi = -500000000LL;
constexpr long long kMaxAi = 500000000LL;

long long bounded(long long value) {
    return max(kMinAi, min(kMaxAi, value));
}

vector<long long> makeFlat(int n) {
    long long value = rnd.next(-20, 20);
    return vector<long long>(n, value);
}

vector<long long> makeAlternating(int n) {
    long long low = rnd.next(-30, 0);
    long long high = rnd.next(0, 30);
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = (i % 2 == 0 ? low : high);
    }
    if (rnd.next(2) == 1) {
        reverse(a.begin(), a.end());
    }
    return a;
}

vector<long long> makeWalk(int n) {
    vector<long long> a(n);
    a[0] = rnd.next(-25, 25);
    int maxStep = rnd.next(1, 12);
    for (int i = 1; i < n; ++i) {
        a[i] = bounded(a[i - 1] + rnd.next(-maxStep, maxStep));
    }
    return a;
}

vector<long long> makeSpike(int n) {
    long long base = rnd.next(-15, 15);
    vector<long long> a(n, base);
    int spikes = rnd.next(1, min(n, 4));
    for (int i = 0; i < spikes; ++i) {
        int pos = rnd.next(n);
        a[pos] = bounded(base + rnd.next(-80, 80));
    }
    return a;
}

vector<long long> makeBoundary(int n) {
    vector<long long> choices = {
        kMinAi,
        kMinAi + rnd.next(0, 10),
        -1,
        0,
        1,
        kMaxAi - rnd.next(0, 10),
        kMaxAi,
    };
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rnd.any(choices);
    }
    return a;
}

vector<long long> makeCase(int n) {
    int mode = rnd.next(5);
    if (mode == 0) return makeFlat(n);
    if (mode == 1) return makeAlternating(n);
    if (mode == 2) return makeWalk(n);
    if (mode == 3) return makeSpike(n);
    return makeBoundary(n);
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0 && rnd.next(3) == 0) {
            n = 2;
        } else {
            n = rnd.next(2, 18);
        }

        vector<long long> a = makeCase(n);
        println(n);
        println(a);
    }

    return 0;
}
