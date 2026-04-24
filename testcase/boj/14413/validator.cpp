#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 500000, "Q");
    inf.readEoln();

    // Read the array of N natural integers < 1e9
    // Natural integers here are assumed to be >= 1
    vector<int> a = inf.readInts(N, 1, 999999999, "a_i");
    inf.readEoln();

    // Read Q queries
    for (int i = 0; i < Q; i++) {
        int L = inf.readInt(1, N, "L_i");
        inf.readSpace();
        int R = inf.readInt(1, N, "R_i");
        ensuref(R >= L,
                "For query index %d, R (%d) is less than L (%d)",
                i, R, L);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
