#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 200000, "K");
    inf.readSpace();
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    vector<int> A = inf.readInts(N, 1, N, "A_i");
    inf.readEoln();

    for (int i = 0; i < Q; ++i) {
        int l = inf.readInt(1, N, "l");
        inf.readSpace();
        int r = inf.readInt(l, N, "r");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
