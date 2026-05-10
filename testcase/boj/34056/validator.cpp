#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(2, 200000, "N");
    inf.readEoln();

    // 2. Read D_1 ... D_N
    vector<int> D = inf.readInts(N, 1, 1000000000, "D_i");
    inf.readEoln();

    // 3. Read Q
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // 4. Read Q queries, at least one type 2 must appear
    int type2_count = 0;
    for (int i = 0; i < Q; ++i) {
        int op = inf.readInt(1, 2, "op");
        inf.readSpace();

        if (op == 1) {
            // 1 c x
            int c = inf.readInt(1, N-1, "c");
            inf.readSpace();
            int x = inf.readInt(1, 1000000000, "x");
            inf.readEoln();
        } else {
            // 2 c
            int c = inf.readInt(1, N, "c");
            inf.readEoln();
            ++type2_count;
        }
    }

    ensuref(type2_count >= 1, "There must be at least one type 2 query.");

    inf.readEof();
}
