#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read array A of size N
    vector<long long> A = inf.readLongs(N, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    // Read M queries
    for (int i = 0; i < M; i++) {
        int s = inf.readInt(1, N, "s_i");
        inf.readSpace();
        int e = inf.readInt(1, N, "e_i");
        inf.readEoln();
        ensuref(s <= e,
                "Query %d is invalid: s (%d) > e (%d)", 
                i + 1, s, e);
    }

    inf.readEof();
    return 0;
}
