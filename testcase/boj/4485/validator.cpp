#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int test_count = 0;
    while (true) {
        // Read N, allow 0 to detect end, but enforce N==0 or 2<=N<=125
        int N = inf.readInt(0, 125, "N");
        inf.readEoln();
        if (N == 0) break;
        // Count and limit number of test cases
        test_count++;
        ensuref(test_count <= 100000,
                "Number of test cases must be at most 100000, found %d", test_count);
        ensuref(N >= 2,
                "N must be either 0 (to end) or between 2 and 125, got %d", N);

        // Read the grid: N rows of N integers [0..9] each
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                // name each cell for clarity
                char buf[32];
                sprintf(buf, "grid[%d][%d]", i, j);
                int cell = inf.readInt(0, 9, buf);
                if (j + 1 < N) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    inf.readEof();
    return 0;
}
