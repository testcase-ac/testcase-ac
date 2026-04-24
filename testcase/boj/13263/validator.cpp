#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read a_i
    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    // Read b_i
    vector<long long> b = inf.readLongs(n, 0LL, 1000000000LL, "b_i");
    inf.readEoln();

    // Validate constraints:
    // a_1 = 1
    ensuref(a[0] == 1LL, "a_1 must be 1, found %lld", a[0]);
    // a is strictly increasing
    for (int i = 1; i < n; i++) {
        ensuref(a[i] > a[i-1],
                "a must be strictly increasing but a[%d]=%lld <= a[%d]=%lld",
                i+1, a[i], i, a[i-1]);
    }
    // b_n = 0
    ensuref(b[n-1] == 0LL, "b_n must be 0, found %lld", b[n-1]);
    // b is strictly decreasing
    for (int i = 1; i < n; i++) {
        ensuref(b[i-1] > b[i],
                "b must be strictly decreasing but b[%d]=%lld <= b[%d]=%lld",
                i, b[i-1], i+1, b[i]);
    }

    inf.readEof();
    return 0;
}
