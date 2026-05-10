#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of players N
    int n = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read initial strengths a1..aN, must be between 1 and 1e9
    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    // They must be in non-decreasing order
    for (int i = 1; i < n; ++i) {
        ensuref(a[i-1] <= a[i],
                "Initial strengths must be non-decreasing: a[%d]=%lld > a[%d]=%lld",
                i, a[i-1], i+1, a[i]);
    }

    inf.readEof();
    return 0;
}
