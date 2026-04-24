#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the N x N cake sweetness matrix
    for (int i = 1; i <= N; i++) {
        // Read exactly N integers in [1,1000]
        inf.readInts(N, 1, 1000, "C");
        inf.readEoln();
    }

    // No extra characters
    inf.readEof();
    return 0;
}
