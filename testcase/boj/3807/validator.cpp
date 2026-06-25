#include "testlib.h"

#include <set>

using namespace std;

bool isPrime(int x) {
    if (x < 2) {
        return false;
    }
    for (int d = 2; d * d <= x; ++d) {
        if (x % d == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 500, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int c = inf.readInt(1, 15, "C");
        inf.readEoln();

        set<int> primes;
        for (int i = 1; i <= c; ++i) {
            int p = inf.readInt(2, 1000, "P_i");
            inf.readSpace();
            inf.readInt(1, 50, "a_i");
            inf.readEoln();

            ensuref(isPrime(p), "P_%d is not prime: %d", i, p);
            ensuref(primes.insert(p).second, "duplicate prime factor P_%d: %d", i, p);
        }
    }

    inf.readEof();
    return 0;
}
