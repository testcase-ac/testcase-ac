#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 1000;
    const int MAX_K = 100000;
    const int MAX_TOTAL_K = 1000000;
    const int MAX_L = 10000;
    const int MAX_NOTE = 10000;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readEoln();

    long long totalK = 0;
    for (int i = 1; i <= n; ++i) {
        int k = inf.readInt(2, MAX_K, "K_i");
        totalK += k;
        ensuref(totalK <= MAX_TOTAL_K,
                "sum of K_i exceeds %d after song %d: %lld",
                MAX_TOTAL_K, i, totalK);

        for (int j = 1; j <= k; ++j) {
            inf.readSpace();
            inf.readInt(1, MAX_NOTE, "a_ij");
        }
        inf.readEoln();
    }

    int l = inf.readInt(2, MAX_L, "L");
    inf.readEoln();

    inf.readInts(l, 1, MAX_NOTE, "b_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
