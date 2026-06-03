#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int scenarios = inf.readInt(1, 100000, "scenarios");
    inf.readEoln();

    int total_pairs = 0;
    for (int scenario = 1; scenario <= scenarios; ++scenario) {
        setTestCase(scenario);

        int n = inf.readInt(1, 1000000, "n");
        inf.readEoln();

        int k = inf.readInt(1, 100000, "k");
        inf.readEoln();
        total_pairs += k;
        // CHECK: The statement gives per-scenario limits but no total scenario
        // or total input-size limit. Cap total pair lines to keep inputs practical.
        ensuref(total_pairs <= 2000000,
                "too many total friendship/request pairs after scenario %d: %d",
                scenario, total_pairs);

        for (int i = 1; i <= k; ++i) {
            int a = inf.readInt(0, n - 1, "a");
            inf.readSpace();
            int b = inf.readInt(0, n - 1, "b");
            inf.readEoln();
            // CHECK: The statement does not explicitly forbid self-loops or
            // duplicate friendship entries, so this validator accepts them.
            (void)a;
            (void)b;
        }

        int m = inf.readInt(1, 100000, "m");
        inf.readEoln();
        total_pairs += m;
        ensuref(total_pairs <= 2000000,
                "too many total friendship/request pairs after scenario %d: %d",
                scenario, total_pairs);

        for (int i = 1; i <= m; ++i) {
            inf.readInt(0, n - 1, "u");
            inf.readSpace();
            inf.readInt(0, n - 1, "v");
            inf.readEoln();
        }
    }

    inf.readEof();
}
