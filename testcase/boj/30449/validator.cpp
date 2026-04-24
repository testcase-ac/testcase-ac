#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 5000, "n");
    inf.readSpace();
    long long k = inf.readLong(1LL, 10000000LL, "k");
    inf.readEoln();

    // Compute sum_{d=1..n} phi(d)
    vector<int> phi(n+1);
    for (int i = 0; i <= n; i++) {
        phi[i] = i;
    }
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) { // i is prime
            for (int j = i; j <= n; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    // sum phi
    long long sumPhi = 0;
    for (int i = 1; i <= n; i++) {
        sumPhi += phi[i];
    }
    // total size of R(n) is 1 (for 0/1) + sumPhi
    long long total = sumPhi + 1;
    ensuref(k <= total,
            "k (%lld) must be <= |R(n)| = 1 + sum_{d=1..n} phi(d) = %lld",
            k, total);

    inf.readEof();
    return 0;
}
