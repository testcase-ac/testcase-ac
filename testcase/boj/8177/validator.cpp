#include "testlib.h"
#include <vector>
#include <cassert>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, m, k, d
    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500000, "m");
    inf.readSpace();
    int k = inf.readInt(1, 1000000000, "k");
    inf.readSpace();
    int d = inf.readInt(0, n-1, "d");
    inf.readEoln();

    // For each foot size r, track current number of members
    // r in [1, n-d]
    int max_r = n - d;
    vector<long long> members(max_r + 2, 0); // 1-based, up to max_r

    for (int i = 0; i < m; ++i) {
        int r = inf.readInt(1, max_r, "r_i");
        inf.readSpace();
        long long x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readEoln();

        // Check that no one leaves who never joined
        if (x < 0) {
            ensuref(members[r] + x >= 0,
                "At event %d: trying to remove %lld members with foot size %d, but only %lld present.",
                i+1, -x, r, members[r]);
        }

        // Update members
        members[r] += x;
        // No further checks: the problem only guarantees that "the sequence is sensible, i.e. someone who never joined the club cannot leave it."
        // The validator should NOT check if the answer is always TAK or always exists, only that the input is valid and sensible.
    }

    inf.readEof();
}
