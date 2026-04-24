#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K with spacing and line ending
    int N = inf.readInt(1, 15, "N");
    inf.readSpace();
    int M = inf.readInt(1, 15, "M");
    inf.readSpace();
    int total = N * M;
    // K = 0 means no marked cell; otherwise must be 2 <= K <= total-1
    int K = inf.readInt(0, total - 1, "K");
    inf.readEoln();

    // Validate that N and M are not both 1
    ensuref(!(N == 1 && M == 1),
            "Invalid grid size: N and M cannot both be 1 (got N=%d, M=%d)", N, M);

    // Validate K according to problem statement
    ensuref(K == 0 || (K > 1 && K < total),
            "Invalid K: must be 0 or in [2, N*M-1] (got K=%d, N*M=%d)", K, total);

    inf.readEof();
    return 0;
}
