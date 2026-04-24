#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long M = inf.readLong(1LL, 1000000000000000000LL, "M");
    inf.readEoln();

    // Read haybales
    vector<long long> F(N), S(N);
    for (int i = 0; i < N; i++) {
        F[i] = inf.readLong(1LL, 1000000000LL, "F_i");
        inf.readSpace();
        S[i] = inf.readLong(1LL, 1000000000LL, "S_i");
        inf.readEoln();
    }

    // Global property: there must exist a contiguous subarray with sum of F >= M
    long long min_prefix = 0;
    long long prefix = 0;
    bool found = false;
    for (int i = 0; i < N; i++) {
        prefix += F[i];
        if (prefix - min_prefix >= M) {
            found = true;
            break;
        }
        if (prefix < min_prefix) {
            min_prefix = prefix;
        }
    }
    ensuref(found, "No contiguous interval has total flavor >= M (%lld)", M);

    inf.readEof();
    return 0;
}
