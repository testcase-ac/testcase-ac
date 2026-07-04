#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for K; cap the total cases at
    // 100000 and the total candidate rows at 100000 for practical validation.
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    int totalN = 0;
    for (int tc = 1; tc <= k; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "n");
        inf.readEoln();

        totalN += n;
        ensuref(totalN <= 100000,
                "total number of candidate rows exceeds 100000 at data set %d",
                tc);

        for (int i = 1; i <= n; ++i) {
            // CHECK: The statement only says v_i is an even number of voters;
            // allow zero voters and cap each count at 1e9 for practical input size.
            int v = inf.readInt(0, 1000000000, "v_i");
            inf.readEoln();
            ensuref(v % 2 == 0,
                    "v_%d in data set %d is not even: %d",
                    i,
                    tc,
                    v);
        }
    }

    inf.readEof();
    return 0;
}
