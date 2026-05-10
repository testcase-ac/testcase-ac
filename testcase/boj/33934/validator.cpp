#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N S E
    int N = inf.readInt(2, 200000, "N");
    inf.readSpace();
    int S = inf.readInt(1, N, "S");
    inf.readSpace();
    int E = inf.readInt(1, N, "E");
    inf.readEoln();
    ensuref(S != E, "S must be different from E: S=%d, E=%d", S, E);

    // Second line: A_1 ... A_N
    vector<int> A = inf.readInts(N, 1, 1000, "A_i");
    inf.readEoln();

    // Third line: K
    long long K = inf.readLong(2LL, 1000000000LL, "K");
    inf.readEoln();

    inf.readEof();
}
