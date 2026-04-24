#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    long long maxM = 1LL * N * N;
    int M = inf.readInt(1, maxM, "M");
    inf.readEoln();

    // Read M block positions
    for (int i = 0; i < M; i++) {
        int r = inf.readInt(1, N, "R");
        inf.readSpace();
        int c = inf.readInt(1, N, "C");
        inf.readEoln();
    }

    // No more input
    inf.readEof();
    return 0;
}
