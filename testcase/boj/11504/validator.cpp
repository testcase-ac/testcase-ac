#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; tc++) {
        // Read N and M
        int N = inf.readInt(1, 100, "N");
        inf.readSpace();
        int M = inf.readInt(1, 9, "M");
        ensuref(M <= N, "M must be <= N, but M=%d, N=%d", M, N);
        inf.readEoln();

        // Read X digits
        vector<int> X = inf.readInts(M, 0, 9, "X_i");
        inf.readEoln();

        // Read Y digits
        vector<int> Y = inf.readInts(M, 0, 9, "Y_i");
        inf.readEoln();

        // Read spinner state
        vector<int> A = inf.readInts(N, 0, 9, "A_i");
        inf.readEoln();

        // Ensure X <= Y (as M-digit numbers, leading zeros allowed)
        for (int i = 0; i < M; i++) {
            if (X[i] < Y[i]) {
                // good, X < Y
                break;
            } else if (X[i] > Y[i]) {
                ensuref(false,
                        "X must be <= Y, but at position %d: X[%d]=%d > Y[%d]=%d",
                        i+1, i+1, X[i], i+1, Y[i]);
            }
            // else X[i] == Y[i], continue checking
        }
    }

    inf.readEof();
    return 0;
}
