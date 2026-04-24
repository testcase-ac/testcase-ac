#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    long long n = inf.readLong(1LL, 1000000LL, "n");
    inf.readEoln();

    // Read a_i values
    vector<long long> a = inf.readLongs(n, 0LL, 2000000000LL, "a_i");
    inf.readEoln();

    // Check sum constraints: 1 ≤ m = sum(a_i) ≤ 2e9
    __int128 sum = 0;
    for (long long x : a) {
        sum += x;
    }
    ensuref(sum >= 1,
            "Sum of a_i (m) must be at least 1, but got %lld",
            (long long)sum);
    ensuref(sum <= 2000000000LL,
            "Sum of a_i (m) must be at most 2000000000, but got %lld",
            (long long)sum);

    inf.readEof();
    return 0;
}
