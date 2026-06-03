#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no T bound; use the local numeric default.
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalPorts = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // CHECK: Korean statement says N <= 40000; English variant says p < 40000.
        int N = inf.readInt(1, 40000, "N");
        inf.readEoln();

        totalPorts += N;
        // CHECK: There is no total input-size bound; cap numeric scalar volume locally.
        ensuref(totalPorts <= 5000000,
                "total number of ports exceeds local cap: %lld", totalPorts);

        vector<bool> seen(N + 1, false);
        for (int i = 1; i <= N; ++i) {
            int k = inf.readInt(1, N, "k_i");
            inf.readEoln();

            ensuref(!seen[k], "right port %d appears more than once", k);
            seen[k] = true;
        }
    }

    inf.readEof();
}
