#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 50000, "Q");
    inf.readEoln();

    // Read N participant coordinates
    for (int i = 0; i < N; i++) {
        inf.readInts(11, -1000000000, 1000000000, "x");
        inf.readEoln();
    }

    // Read Q parking lot coordinates
    for (int i = 0; i < Q; i++) {
        inf.readInts(11, -1000000000, 1000000000, "y");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
