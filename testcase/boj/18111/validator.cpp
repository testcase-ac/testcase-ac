#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, B
    int N = inf.readInt(1, 500, "N");
    inf.readSpace();
    int M = inf.readInt(1, 500, "M");
    inf.readSpace();
    long long B = inf.readLong(0LL, 64000000LL, "B");
    inf.readEoln();

    // Read the terrain heights
    for (int i = 0; i < N; i++) {
        inf.readInts(M, 0, 256, "height");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
