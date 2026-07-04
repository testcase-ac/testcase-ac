#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound the number of scenarios. Use the
    // local multi-case cap and limit aggregate n to one largest scenario.
    int scenarios = inf.readInt(1, 100000, "scenarios");
    inf.readEoln();

    long long sumN = 0;
    for (int scenario = 1; scenario <= scenarios; ++scenario) {
        setTestCase(scenario);

        int b = inf.readInt(2, 1000, "b");
        inf.readSpace();
        int n = inf.readInt(1, 1000000, "n");
        inf.readEoln();

        sumN += n;
        ensuref(sumN <= 1000000LL, "sum of n exceeds 1000000 after scenario %d", scenario);
    }

    inf.readEof();
}
