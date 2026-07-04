#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    int totalCandidates = 0;
    for (int dataset = 1; dataset <= k; ++dataset) {
        setTestCase(dataset);

        int n = inf.readInt(1, 100, "n");
        inf.readEoln();
        totalCandidates += n;
        // CHECK: K has no statement upper bound; cap aggregate datasets to a practical size.
        ensuref(totalCandidates <= 100000,
                "aggregate candidate count exceeds practical cap: %d",
                totalCandidates);

        for (int i = 1; i <= n; ++i) {
            int voters = inf.readInt(1, 1000000, "v_i");
            inf.readEoln();
            ensuref(voters % 2 == 0,
                    "voter count for candidate %d is not even: %d",
                    i,
                    voters);
        }
    }

    inf.readEof();
}
