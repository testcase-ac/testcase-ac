#include "testlib.h"
#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // 2. Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 0, (1LL << 31) - 1, "A_i");
    inf.readEoln();

    // 3. Read M
    int M = inf.readInt(1, 1000000, "M");
    inf.readEoln();

    // 4. Read M queries, and check at least one type 2 and one type 3 query
    bool has_type2 = false, has_type3 = false;
    for (int i = 0; i < M; ++i) {
        int type = inf.readInt(1, 3, "query_type");
        inf.readSpace();

        int L = inf.readInt(1, N, "L");
        inf.readSpace();
        int R = inf.readInt(L, N, "R"); // L <= R <= N

        if (type == 1) {
            inf.readSpace();
            int X = inf.readInt(0, (1LL << 31) - 1, "X");
            inf.readEoln();
        } else if (type == 2) {
            has_type2 = true;
            inf.readEoln();
        } else if (type == 3) {
            has_type3 = true;
            inf.readEoln();
        } else {
            // Should not happen due to readInt(1,3)
            ensuref(false, "Unknown query type %d at line %d", type, i+4);
        }
    }

    ensuref(has_type2, "There must be at least one type 2 query (max query)");
    ensuref(has_type3, "There must be at least one type 3 query (sum query)");

    inf.readEof();
}
