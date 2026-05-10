#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500, "N");
    inf.readEoln();

    // Read T_1 ... T_N
    vector<int> T = inf.readInts(N, 0, 511, "T_i");
    inf.readEoln();

    // Read Q
    int Q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 0; i < Q; ++i) {
        int l = inf.readInt(1, N, "l");
        inf.readSpace();
        int r = inf.readInt(l, N, "r");
        inf.readEoln();
    }

    inf.readEof();
}
