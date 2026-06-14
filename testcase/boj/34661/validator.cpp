#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    int totalArea = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "N");
        inf.readSpace();
        int m = inf.readInt(1, 100, "M");
        inf.readEoln();

        totalArea += n * m;
        ensuref(totalArea <= 10000,
                "sum of N*M exceeds 10000 after case %d: %d", tc, totalArea);

        for (int i = 0; i < n; ++i) {
            string row = inf.readToken("[.x]{1,100}", "grid_row");
            ensuref((int)row.size() == m,
                    "row %d has length %d, expected %d", i + 1, (int)row.size(), m);
            inf.readEoln();
        }
    }

    inf.readEof();
}
