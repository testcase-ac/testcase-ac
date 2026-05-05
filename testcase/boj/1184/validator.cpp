#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read the N x N grid of Aij
    for (int i = 0; i < N; i++) {
        // Each Aij must satisfy -1000 < Aij < 1000, i.e. [-999, 999]
        inf.readInts(N, -999, 999, "Aij");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
