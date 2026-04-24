#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of units
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read initial sizes
    vector<int> init = inf.readInts(N, 1, 1000, "initial_size");
    inf.readEoln();

    // Prepare for updates and queries
    vector<long long> sz(N + 1);
    long long total = 0;
    for (int i = 1; i <= N; i++) {
        sz[i] = init[i - 1];
        total += sz[i];
    }

    // Read number of commands
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Process each command
    for (int j = 0; j < M; j++) {
        int type = inf.readInt(1, 2, "type");
        if (type == 1) {
            // Update command: "1 i a"
            inf.readSpace();
            int idx = inf.readInt(1, N, "unit_index");
            inf.readSpace();
            int delta = inf.readInt(-3000, 3000, "delta");
            // a must be non-zero by problem statement
            ensuref(delta != 0, "Command %d: delta must be non-zero", j);
            inf.readEoln();

            long long new_sz = sz[idx] + (long long)delta;
            ensuref(new_sz >= 0,
                    "Command %d: after applying delta, unit %d size becomes negative (%lld)",
                    j, idx, new_sz);
            sz[idx] = new_sz;
            total += delta;
        } else {
            // Query command: "2 i"
            inf.readSpace();
            // i must be between 1 and current total soldiers
            long long q = inf.readLong(1LL, total, "query_index");
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
