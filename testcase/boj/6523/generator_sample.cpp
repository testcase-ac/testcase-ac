#include "testlib.h"

#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;

namespace {

constexpr int kMaxStepsUntilFirstDies = 1000000;

long long nextSoldier(long long x, long long n, long long a, long long b) {
    return ((__int128)a * x % n * x + b) % n;
}

bool firstDeathOccursWithinLimit(long long n, long long a, long long b) {
    unordered_set<long long> seen;
    seen.reserve(kMaxStepsUntilFirstDies + 1);

    long long x = 0;
    seen.insert(x);
    for (int step = 1; step <= kMaxStepsUntilFirstDies; ++step) {
        x = nextSoldier(x, n, a, b);
        if (!seen.insert(x).second) {
            return true;
        }
    }
    return false;
}

void addCase(vector<tuple<long long, long long, long long>>& cases, long long n,
             long long a, long long b) {
    if (firstDeathOccursWithinLimit(n, a, b)) {
        cases.emplace_back(n, a, b);
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<tuple<long long, long long, long long>> cases;

    int smallCases = rnd.next(3, 7);
    for (int i = 0; i < smallCases; ++i) {
        long long n = rnd.next(2, 80);
        addCase(cases, n, rnd.next(0LL, n - 1), rnd.next(0LL, n - 1));
    }

    int structuredCases = rnd.next(3, 6);
    for (int i = 0; i < structuredCases; ++i) {
        int mode = rnd.next(0, 4);
        long long n = 0;
        long long a = 0;
        long long b = 0;

        if (mode == 0) {
            n = rnd.next(2LL, 1000000000LL);
            a = 0;
            b = rnd.next(0LL, n - 1);
        } else if (mode == 1) {
            n = rnd.next(2LL, 1000000000LL);
            a = rnd.next(0LL, n - 1);
            b = 0;
        } else if (mode == 2) {
            n = rnd.next(2LL, 1000000000LL);
            a = n - 1;
            b = n - 1;
        } else {
            n = rnd.next(2LL, 200000LL);
            a = rnd.next(0LL, n - 1);
            b = rnd.next(0LL, n - 1);
        }

        addCase(cases, n, a, b);
    }

    shuffle(cases.begin(), cases.end());
    for (auto [n, a, b] : cases) {
        println(n, a, b);
    }
    println(0);

    return 0;
}
