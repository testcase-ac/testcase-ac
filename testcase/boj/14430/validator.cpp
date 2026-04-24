#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read dimensions N and M
    int N = inf.readInt(1, 300, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300, "M");
    inf.readEoln();

    // Read the grid: N rows of M integers (0 or 1)
    for (int i = 0; i < N; i++) {
        // Read exactly M cells, each either 0 or 1
        inf.readInts(M, 0, 1, "cell");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
