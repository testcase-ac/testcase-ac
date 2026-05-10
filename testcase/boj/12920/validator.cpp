#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        int V = inf.readInt(1, M, "V");
        inf.readSpace();
        int C = inf.readInt(1, 10000, "C");
        inf.readSpace();
        int K = inf.readInt(1, 10000, "K");
        inf.readEoln();

        // Check V * K <= 10000, use long long to avoid overflow
        long long prod = 1LL * V * K;
        ensuref(prod <= 10000LL, "V * K must be <= 10000, but got V=%d, K=%d, V*K=%lld at item %d", V, K, prod, i+1);
    }

    inf.readEof();
}
