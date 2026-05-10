#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // For checking duplicate constraints (optional, not required by statement)
    // set<tuple<int,int,int,int>> seen_constraints;

    for (int i = 0; i < M; ++i) {
        int l = inf.readInt(0, N-1, "l_i");
        inf.readSpace();
        int r = inf.readInt(0, N-1, "r_i");
        inf.readSpace();
        int k = inf.readInt(1, r-l+1, "k_i"); // r-l+1 is at least 1, since l<=r
        inf.readSpace();
        int value = inf.readInt(0, 1, "value_i");
        inf.readEoln();

        ensuref(l <= r, "Constraint %d: l_i (%d) > r_i (%d)", i+1, l, r);
        // ensuref(seen_constraints.insert({l,r,k,value}).second, "Duplicate constraint at line %d", i+2);
    }

    inf.readEof();
}
