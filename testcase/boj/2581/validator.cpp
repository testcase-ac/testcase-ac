#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read M and N on separate lines
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();
    int N = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Constraint M ≤ N
    ensuref(M <= N, "M (%d) must be ≤ N (%d)", M, N);

    inf.readEof();
    return 0;
}
