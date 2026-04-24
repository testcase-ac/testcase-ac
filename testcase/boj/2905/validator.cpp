#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and X
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int X = inf.readInt(1, 100000, "X");
    ensuref(X <= N, "Constraint violated: X (%d) must be <= N (%d)", X, N);
    inf.readEoln();

    // Read heights
    vector<int> h = inf.readInts(N, 1, 1000000, "h_i");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
