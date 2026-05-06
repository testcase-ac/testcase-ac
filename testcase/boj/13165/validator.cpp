#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1;
    const int N_MAX = 256;
    const long long NL_MAX = 1024000LL;
    const int A_MIN = 0;
    const int A_MAX = 7676767;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int L = inf.readInt(1, (int)NL_MAX, "L");
    inf.readEoln();

    long long prod = 1LL * N * L;
    ensuref(prod <= NL_MAX, "N * L must be <= %lld, but got %d * %d = %lld",
           NL_MAX, N, L, prod);

    for (int i = 0; i < N; ++i) {
        // read exactly L integers in this row
        vector<int> row = inf.readInts(L, A_MIN, A_MAX, "A_ij");
        inf.readEoln();
    }

    inf.readEof();
}
