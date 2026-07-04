#include "testlib.h"

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

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int m = inf.readInt(1, 95, "M");
        inf.readEoln();

        int previousPrime = 1;
        long long totalCards = 0;
        for (int i = 1; i <= m; ++i) {
            int p = inf.readInt(2, 499, "P_i");
            inf.readSpace();
            long long n = inf.readLong(1LL, 1000000000000000LL, "N_i");
            inf.readEoln();

            ensuref(isPrime(p), "P_%d is not prime: %d", i, p);
            ensuref(previousPrime < p,
                    "P_i values must be strictly increasing: previous=%d current=%d",
                    previousPrime, p);
            previousPrime = p;

            ensuref(totalCards <= 1000000000000000LL - n,
                    "sum of N_i exceeds 10^15 after row %d", i);
            totalCards += n;
        }

        ensuref(2LL <= totalCards && totalCards <= 1000000000000000LL,
                "sum of N_i must be between 2 and 10^15, got %lld", totalCards);
    }

    inf.readEof();
}
