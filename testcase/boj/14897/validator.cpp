#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read array A of size N
    vector<int> A = inf.readInts(N, 1, 1000000000, "A_i");
    inf.readEoln();

    // Read Q
    int Q = inf.readInt(1, 1000000, "Q");
    inf.readEoln();

    // Read queries
    for (int i = 0; i < Q; i++) {
        int l = inf.readInt(1, N, "l_i");
        inf.readSpace();
        int r = inf.readInt(l, N, "r_i"); // ensure r >= l
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
