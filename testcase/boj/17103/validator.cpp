#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    // Each test case: a single even integer N, 2 < N <= 1e6
    for (int tc = 0; tc < T; tc++) {
        int N = inf.readInt(4, 1000000, "N"); // N >= 4 ensures N > 2 and even minimal
        ensuref(N % 2 == 0, "N must be even at test case %d: got %d", tc+1, N);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
