#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // 2. Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 0, 1, "A_i");
    inf.readEoln();

    // 3. Read K queries, each (l_i, r_i)
    for (int i = 0; i < K; ++i) {
        int l = inf.readInt(1, N, "l_i");
        inf.readSpace();
        int r = inf.readInt(l, N, "r_i");
        inf.readEoln();
    }

    inf.readEof();
}
