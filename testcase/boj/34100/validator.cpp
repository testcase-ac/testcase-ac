#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 300000, "T");
    inf.readEoln();

    long long totalCells = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 3000, "N");
        inf.readSpace();
        int m = inf.readInt(2, 3000, "M");
        inf.readEoln();

        totalCells += 1LL * n * m;
        ensuref(totalCells <= 3000LL * 3000LL,
                "sum of N*M exceeds 3000^2 after testcase %d", tc);

        const string rowPattern = "[#.]{" + to_string(m) + "}";
        for (int i = 0; i < n; ++i) {
            inf.readLine(rowPattern, "row");
        }
    }

    inf.readEof();
}
