#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalCells = 0;
    int testCaseCount = 0;

    while (!inf.seekEof()) {
        ++testCaseCount;
        setTestCase(testCaseCount);

        int n = inf.readInt(2, 2000, "N");
        inf.readEoln();

        // CHECK: the statement has no test case count, so cap aggregate matrix
        // size at one largest test case to keep validation and fixed inputs practical.
        totalCells += 1LL * n * n;
        ensuref(totalCells <= 4000000LL,
                "sum of N^2 across test cases exceeds 4000000");

        vector<vector<int>> d(n, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                d[i][j] = inf.readInt(0, 1000000, "distance");
            }
            inf.readEoln();
        }

        for (int i = 0; i < n; ++i) {
            ensuref(d[i][i] == 0,
                    "distance from city %d to itself must be 0, found %d",
                    i + 1,
                    d[i][i]);
            for (int j = i + 1; j < n; ++j) {
                ensuref(d[i][j] > 0,
                        "distance between distinct cities %d and %d must be positive, found %d",
                        i + 1,
                        j + 1,
                        d[i][j]);
                ensuref(d[i][j] == d[j][i],
                        "distances for cities %d and %d are not symmetric: %d vs %d",
                        i + 1,
                        j + 1,
                        d[i][j],
                        d[j][i]);
            }
        }
    }

    ensuref(testCaseCount > 0, "input must contain at least one test case");
    inf.readEof();
}
