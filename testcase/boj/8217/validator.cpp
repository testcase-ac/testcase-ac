#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300000, "M");
    inf.readEoln();

    // Read ownership array o_i of length M
    vector<int> o = inf.readInts(M, 1, N, "o_i");
    inf.readEoln();

    // Read target samples p_j for each of N countries
    vector<long long> p = inf.readLongs(N, 1LL, 1000000000LL, "p_j");
    inf.readEoln();

    // Read number of forecasts Q
    int Q = inf.readInt(1, 300000, "Q");
    inf.readEoln();

    // Read each forecast line: l_u, r_u, a_u
    for (int u = 1; u <= Q; u++) {
        int l = inf.readInt(1, M, "l_u");
        inf.readSpace();
        int r = inf.readInt(1, M, "r_u");
        inf.readSpace();
        long long a = inf.readLong(1LL, 1000000000LL, "a_u");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
