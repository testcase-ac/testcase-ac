#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxP = 3000000;
    vector<bool> isPrime(maxP + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= maxP; ++i) {
        if (!isPrime[i]) {
            continue;
        }
        for (int j = i * i; j <= maxP; j += i) {
            isPrime[j] = false;
        }
    }

    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    vector<bool> seen(maxP + 1, false);
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int p = inf.readInt(1, maxP, "p_i");
        ensuref(isPrime[p], "p_i must be prime at index %d: %d", i + 1, p);
        ensuref(!seen[p], "duplicate prime at index %d: %d", i + 1, p);
        seen[p] = true;
    }
    inf.readEoln();

    inf.readLong(1LL, 1000000000000LL, "K");
    inf.readEoln();
    inf.readEof();
}
