#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and Q
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // Read a_1 ... a_N
    vector<int> a = inf.readInts(N, 1, 1000, "a_i");
    inf.readEoln();

    // Read Q queries, each (l, r)
    for (int i = 0; i < Q; ++i) {
        int l = inf.readInt(1, N-1, "l");
        inf.readSpace();
        int r = inf.readInt(l+1, N, "r");
        inf.readEoln();
        ensuref(l < r, "In query %d: l (%d) must be less than r (%d)", i+1, l, r);
    }

    inf.readEof();
}
