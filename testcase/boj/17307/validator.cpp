#include "testlib.h"
#include <vector>
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and C
    int N = inf.readInt(1, 250000, "N");
    inf.readSpace();
    int C = inf.readInt(1, 1000000000, "C");
    inf.readEoln();

    // Read X_i
    vector<int> X = inf.readInts(N, 0, C-1, "X_i");
    inf.readEoln();

    // Check that all X_i are in [0, C-1]
    for (int i = 0; i < N; ++i) {
        ensuref(0 <= X[i] && X[i] < C, "X[%d]=%d is not in [0, C-1=%d]", i+1, X[i], C-1);
    }

    inf.readEof();
}
