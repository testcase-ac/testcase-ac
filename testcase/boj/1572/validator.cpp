#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 250000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 5000, "K");
    inf.readEoln();

    // Must have N >= K
    ensuref(N >= K, "N must be at least K, but N=%d, K=%d", N, K);

    // Read N temperature readings, one per line
    for (int i = 0; i < N; i++) {
        inf.readInt(0, 65536, "temperature");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
