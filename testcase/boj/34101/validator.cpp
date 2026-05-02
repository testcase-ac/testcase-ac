#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // 2. Read a_1 ... a_N
    vector<int> a = inf.readInts(N, 1, N, "a_i");
    inf.readEoln();

    // 3. Read Q
    int Q = inf.readInt(1, 1000000, "Q");
    inf.readEoln();

    // 4. Read Q queries
    for (int j = 0; j < Q; ++j) {
        int l = inf.readInt(1, N, "l_j");
        inf.readSpace();
        int r = inf.readInt(l, N, "r_j"); // l <= r <= N
        inf.readEoln();
    }

    inf.readEof();
}
