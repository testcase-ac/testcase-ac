#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read initial array A of size N
    vector<int> A = inf.readInts(N, 1, 1000000000, "A_i");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read M queries
    for (int qi = 0; qi < M; qi++) {
        // Query type: 1 or 2
        int type = inf.readInt(1, 2, "q_type");
        inf.readSpace();
        if (type == 1) {
            // Update: 1 i v
            int idx = inf.readInt(1, N, "q_i");
            inf.readSpace();
            int v = inf.readInt(1, 1000000000, "q_v");
            inf.readEoln();
        } else {
            // Query: 2 l r
            int l = inf.readInt(1, N, "q_l");
            inf.readSpace();
            int r = inf.readInt(l, N, "q_r");
            inf.readEoln();
        }
    }

    // No extra characters
    inf.readEof();
    return 0;
}
