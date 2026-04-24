#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    int N = inf.readInt(1, 300, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300, "M");
    inf.readEoln();

    // Check the product constraint N * M <= 300
    ensuref(1LL * N * M <= 300,
            "Constraint violated: N * M must be <= 300, but got N=%d, M=%d, N*M=%d",
            N, M, N * M);

    inf.readEof();
    return 0;
}
