#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 3000, "N");
    inf.readEoln();

    // Read positions X_i
    vector<int> X = inf.readInts(N, 1, 100000000, "X_i");
    inf.readEoln();
    for (int i = 1; i < N; i++) {
        // Check strictly increasing
        ensuref(X[i] > X[i-1],
                "X_%d = %d is not greater than X_%d = %d",
                i+1, X[i], i, X[i-1]);
    }

    // Read times T_i
    vector<int> T = inf.readInts(N, 0, 100000000, "T_i");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
