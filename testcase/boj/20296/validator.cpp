#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(0, 1000, "m");
    inf.readSpace();
    int M = inf.readInt(m, 1000, "M");
    inf.readSpace();
    int K = inf.readInt(0, 1000000, "K");
    inf.readEoln();

    ensuref(1LL * n * m <= K, "K must be at least N*m: N=%d m=%d K=%d", n, m, K);
    ensuref(K <= 1LL * n * M, "K must be at most N*M: N=%d M=%d K=%d", n, M, K);

    inf.readEof();
}
