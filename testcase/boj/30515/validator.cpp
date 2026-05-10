#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MIN = 1;
    const int N_MAX = 200000;
    const int Q_MIN = 1;
    const int Q_MAX = 200000;
    const int A_MIN = 1;
    const int A_MAX = 1000000000;
    const int K_MIN = 1;
    const int K_MAX = 1000000000;

    int N = inf.readInt(N_MIN, N_MAX, "N");
    inf.readEoln();

    // Read A_1..A_N
    vector<int> A = inf.readInts(N, A_MIN, A_MAX, "A_i");
    inf.readEoln();

    int Q = inf.readInt(Q_MIN, Q_MAX, "Q");
    inf.readEoln();

    bool hasType1 = false;

    for (int qi = 0; qi < Q; ++qi) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int l = inf.readInt(1, N, "l");
        inf.readSpace();
        int r = inf.readInt(1, N, "r");
        ensuref(l <= r, "Query %d has l > r: l=%d, r=%d", qi + 1, l, r);

        if (type == 1) {
            inf.readSpace();
            int k = inf.readInt(K_MIN, K_MAX, "k");
            inf.readEoln();
            hasType1 = true;
        } else { // type == 2
            inf.readEoln();
        }
    }

    ensuref(hasType1, "There must be at least one type-1 query.");

    inf.readEof();
}
