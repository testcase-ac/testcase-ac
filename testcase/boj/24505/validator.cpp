#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read A[1..N]
    vector<int> A = inf.readInts(N, 1, N, "A_i");
    inf.readEoln();

    // No further constraints in the statement.
    // But let's check for global formatting rules.

    inf.readEof();
}
