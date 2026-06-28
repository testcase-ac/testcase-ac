#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long maxScalars = 5000000;
    long long scalarCount = 0;

    auto noteScalars = [&](long long count) {
        scalarCount += count;
        // CHECK: c has no statement upper bound, so cap total scalar tokens to keep inputs practical.
        ensuref(scalarCount <= maxScalars, "too many scalar tokens: %lld", scalarCount);
    };

    int c = inf.readInt(1, 100000, "c");
    noteScalars(1);
    inf.readEoln();

    for (int tc = 1; tc <= c; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(1, 1000, "m");
        noteScalars(2);
        inf.readEoln();

        long long visitsInCase = 0;
        for (int i = 1; i <= n; ++i) {
            int t = inf.readInt(0, 1000000, "t");
            inf.readSpace();
            int k = inf.readInt(1, 1000000, "k");
            noteScalars(2);

            visitsInCase += k;
            ensuref(visitsInCase <= 1000000,
                    "case %d has too many scheduled visits: %lld", tc, visitsInCase);
            noteScalars(k);

            for (int j = 1; j <= k; ++j) {
                inf.readSpace();
                inf.readInt(1, m, "g_j");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
