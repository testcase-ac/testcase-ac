#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 100000, "z");
    inf.readEoln();

    int totalK = 0;
    for (int tc = 1; tc <= z; ++tc) {
        setTestCase(tc);

        int k = inf.readInt(1, 10000, "k");
        totalK += k;
        // CHECK: z has no explicit upper bound; local policy caps aggregate work to one maximum-size case.
        ensuref(totalK <= 10000,
                "sum of k exceeds practical cap 10000 after testcase %d", tc);

        for (int i = 1; i <= k; ++i) {
            inf.readSpace();
            inf.readInt(0, 100000, "sheep_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
