#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int tc = 0;
    while (true) {
        // Read number of stages N, allow 0 for termination
        int N = inf.readInt(0, 16, "N");
        inf.readEoln();
        if (N == 0) {
            break;
        }
        tc++;
        setTestCase(tc);
        // Implicitly N >= 1 here
        // Read N lines, each with N+1 integers t_{i0} ... t_{iN}
        for (int i = 1; i <= N; i++) {
            // Each time we read exactly N+1 integers in [1,100000]
            vector<int> row = inf.readInts(N + 1, 1, 100000, "t_i_j");
            inf.readEoln();
        }
        // Limit on number of datasets
        ensuref(tc <= 100000, "Number of datasets exceeds 100000");
    }

    inf.readEof();
    return 0;
}
