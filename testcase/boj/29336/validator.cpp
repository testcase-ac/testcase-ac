#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    vector<long long> a = inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    long long previous_t = 0;
    long long previous_q = 0;
    for (int i = 1; i <= m; ++i) {
        long long t = inf.readLong(1LL, 1000000000LL, "t_i");
        inf.readSpace();
        long long q = inf.readLong(1LL, 1000000000LL, "q_i");
        inf.readEoln();

        // CHECK: The statement says T and Q are in ascending order; accept equal
        // adjacent values as nondecreasing order rather than requiring strict growth.
        ensuref(previous_t <= t, "t_i must be nondecreasing at index %d", i);
        ensuref(previous_q <= q, "q_i must be nondecreasing at index %d", i);
        previous_t = t;
        previous_q = q;
    }

    inf.readEof();
}
