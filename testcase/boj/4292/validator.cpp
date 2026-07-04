#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxP = 100000;
    vector<bool> isPrime(maxP + 1, true);
    isPrime[0] = false;
    isPrime[1] = false;
    for (int i = 2; i * i <= maxP; ++i) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= maxP; j += i) {
            isPrime[j] = false;
        }
    }

    long long sumP = 0;
    while (true) {
        int p = inf.readInt(0, maxP, "p");
        inf.readEoln();

        if (p == 0) break;

        ensuref(isPrime[p], "p must be prime, got %d", p);
        sumP += p;
        // CHECK: the statement gives no case count bound; cap total output-sized work.
        ensuref(sumP <= maxP, "sum of p values must be at most %d", maxP);
    }

    inf.readEof();
}
