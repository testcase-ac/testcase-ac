#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        // Read N, M, K for each test case
        int N = inf.readInt(1, 3000, "N");
        inf.readSpace();
        // M must satisfy N <= M <= 100000
        int M = inf.readInt(N, 100000, "M");
        inf.readSpace();
        // K must satisfy 1 <= K <= N
        int K = inf.readInt(1, N, "K");
        inf.readEoln();
        // No further global constraints implied by the problem
    }

    inf.readEof();
    return 0;
}
