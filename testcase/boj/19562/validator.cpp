#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MOD = 998244353;
    const int N_MIN = 1;
    const int N_MAX = 500;
    const int Q_MIN = 1;
    const int Q_MAX = 250000;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int Q = inf.readInt(Q_MIN, Q_MAX, "Q");
    inf.readEoln();

    // Read N x N matrix A with entries in [0, MOD-1]
    for (int i = 0; i < N; ++i) {
        // use readInts to enforce exact N integers per line
        vector<int> row = inf.readInts(N, 0, MOD - 1, "a_ij");
        inf.readEoln();
    }

    // Read Q query integers in one line, each in [0, MOD-1]
    vector<int> queries = inf.readInts(Q, 0, MOD - 1, "x_i");
    inf.readEoln();

    inf.readEof();
}
