#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and check it's one of {2,4,8,16,32,64,128}
    int N = inf.readInt(2, 128, "N");
    // Must be power of two
    ensuref((N & (N - 1)) == 0, "N (%d) is not a power of two in [2,128]", N);
    inf.readEoln();

    // Read the N×N matrix of colors (0 or 1)
    for (int i = 0; i < N; i++) {
        auto row = inf.readInts(N, 0, 1, "color");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
