#include "testlib.h"
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and Q
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // 2. Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 1, 1000000000, "A_i");
    inf.readEoln();

    // 3. Read Q queries, at least one type 2 query must exist
    int type2_count = 0;
    for (int q = 0; q < Q; ++q) {
        int t = inf.readInt(1, 2, "query_type");
        if (t == 1) {
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int x = inf.readInt(1, 1000000000, "x");
            inf.readEoln();
        } else {
            // t == 2
            inf.readSpace();
            int i = inf.readInt(1, N, "i");
            inf.readEoln();
            ++type2_count;
        }
    }
    ensuref(type2_count >= 1, "There must be at least one type 2 query.");

    inf.readEof();
}
