#include "testlib.h"

#include <unordered_set>

using namespace std;

namespace {

constexpr long long kMaxN = 1000000000LL;
constexpr int kMaxStepsUntilFirstDies = 1000000;
constexpr int kMaxCases = 100000;

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

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        long long n = inf.readLong(0LL, kMaxN, "N_or_sentinel");
        if (n == 0) {
            inf.readEoln();
            break;
        }

        ++cases;
        // CHECK: The statement gives no test-case count; use the local default cap.
        ensuref(cases <= kMaxCases, "too many test cases: %d", cases);

        ensuref(n >= 2, "N must be at least 2, found %lld", n);
        inf.readSpace();
        long long a = inf.readLong(0LL, n - 1, "a");
        inf.readSpace();
        long long b = inf.readLong(0LL, n - 1, "b");
        inf.readEoln();

        setTestCase(cases);
        ensuref(firstDeathOccursWithinLimit(n, a, b),
                "no soldier dies within %d steps for N=%lld, a=%lld, b=%lld",
                kMaxStepsUntilFirstDies, n, a, b);
    }

    inf.readEof();
}
