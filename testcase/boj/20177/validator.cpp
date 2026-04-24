#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    // Read fluctuation values
    vector<long long> a = inf.readLongs(n, -1000000000LL, 1000000000LL, "a");
    inf.readEoln();

    // Read queries
    for (int i = 0; i < m; i++) {
        int S = inf.readInt(1, n, "S_i");
        inf.readSpace();
        int E = inf.readInt(1, n, "E_i");
        inf.readSpace();
        long long U = inf.readLong(-100000000000000LL, 100000000000000LL, "U_i");
        inf.readEoln();

        ensuref(S <= E,
                "Query %d: invalid range [S_i, E_i] = [%d, %d], expected S_i <= E_i",
                i+1, S, E);
    }

    inf.readEof();
    return 0;
}
