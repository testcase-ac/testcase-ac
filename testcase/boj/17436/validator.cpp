#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readSpace();
    long long m = inf.readLong(1LL, 1000000000000LL, "M");
    inf.readEoln();

    vector<int> primes = inf.readInts(n, 2, 100, "p_i");
    inf.readEoln();

    set<int> seen;
    for (int i = 0; i < n; ++i) {
        ensuref(isPrime(primes[i]), "p_%d is not prime: %d", i + 1, primes[i]);
        ensuref(seen.insert(primes[i]).second, "duplicate prime p_%d: %d", i + 1, primes[i]);
    }

    inf.readEof();
}
