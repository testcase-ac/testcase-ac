#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // Read sequence A of length N
    vector<int> A = inf.readInts(N, 1, 100000, "A");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read each query l_i, r_i
    for (int i = 0; i < M; i++) {
        int l = inf.readInt(1, N, "l_i");
        inf.readSpace();
        int r = inf.readInt(1, N, "r_i");
        ensuref(r >= l,
                "Query %d: r_i (%d) must be at least l_i (%d)", 
                i+1, r, l);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
