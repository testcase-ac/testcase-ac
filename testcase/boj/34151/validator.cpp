#include "testlib.h"

#include <vector>

using namespace std;

namespace {

constexpr int kMaxP = 1000000;

vector<bool> buildPrimeTable() {
    vector<bool> isPrime(kMaxP + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; i * i <= kMaxP; ++i) {
        if (!isPrime[i]) {
            continue;
        }
        for (int j = i * i; j <= kMaxP; j += i) {
            isPrime[j] = false;
        }
    }
    return isPrime;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const vector<bool> isPrime = buildPrimeTable();

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int p = inf.readInt(2, kMaxP, "p");
        inf.readSpace();
        long long n = inf.readLong(1LL, 1000000000000000000LL, "n");
        inf.readSpace();
        long long m = inf.readLong(1LL, 1000000000000000000LL, "m");
        inf.readEoln();

        ensuref(isPrime[p], "p must be prime, got %d", p);
        (void)n;
        (void)m;
    }

    inf.readEof();
}
