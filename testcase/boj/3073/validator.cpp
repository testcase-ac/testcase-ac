#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCnt = 0;
    while (true) {
        // Read N, M (allow 0 for sentinel)
        int N = inf.readInt(0, 100, "N");
        inf.readSpace();
        int M = inf.readInt(0, 100, "M");
        inf.readEoln();

        // Sentinel to end input
        if (N == 0 && M == 0) {
            break;
        }

        // New test case
        testCnt++;
        ensuref(testCnt <= 100000, "Number of test cases exceeds 100000");
        setTestCase(testCnt);

        // Validate N, M constraints
        ensuref(N >= 2, "N must be between 2 and 100, got %d", N);
        ensuref(M >= 2, "M must be between 2 and 100, got %d", M);

        // Read the grid
        int cntH = 0, cntm = 0;
        for (int i = 0; i < N; i++) {
            string row = inf.readLine("[^]+", "row");
            ensuref((int)row.size() == M,
                    "Row %d length is %d, expected %d", i+1, (int)row.size(), M);
            for (int j = 0; j < M; j++) {
                char c = row[j];
                ensuref(c == '.' || c == 'H' || c == 'm',
                        "Invalid character at row %d, col %d: %c", i+1, j+1, c);
                if (c == 'H') cntH++;
                if (c == 'm') cntm++;
            }
        }

        // Validate counts of houses and children
        ensuref(cntH == cntm,
                "The number of houses 'H' (%d) and children 'm' (%d) must be equal", cntH, cntm);
        ensuref(cntH <= 100,
                "Number of houses exceeds 100: %d", cntH);
    }

    inf.readEof();
    return 0;
}
