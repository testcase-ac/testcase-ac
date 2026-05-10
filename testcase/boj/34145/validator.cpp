#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M, Q
    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(2, 1000, "M");
    inf.readSpace();
    int Q = inf.readInt(0, 10000, "Q");
    inf.readEoln();

    // 2. Read grid
    string allowed = "EWFA";
    for (int i = 1; i <= N; ++i) {
        string row = inf.readToken("[EWFA]{"+to_string(M)+"}", "B_row");
        ensuref((int)row.size() == M, "Row %d does not have exactly M=%d characters", i, M);
        for (int j = 0; j < M; ++j) {
            ensuref(allowed.find(row[j]) != string::npos, "Invalid character '%c' at row %d, column %d", row[j], i, j+1);
        }
        inf.readEoln();
    }

    // 3. Read Q queries
    for (int i = 1; i <= Q; ++i) {
        int t = inf.readInt(1, 2, "t_i");
        inf.readSpace();
        int r1 = inf.readInt(1, N, "r1_i");
        inf.readSpace();
        int c1 = inf.readInt(1, M, "c1_i");
        inf.readSpace();
        int r2 = inf.readInt(r1, N, "r2_i");
        inf.readSpace();
        int c2 = inf.readInt(c1, M, "c2_i");
        inf.readEoln();

        ensuref(r1 <= r2, "Query %d: r1_i (%d) > r2_i (%d)", i, r1, r2);
        ensuref(c1 <= c2, "Query %d: c1_i (%d) > c2_i (%d)", i, c1, c2);
    }

    inf.readEof();
}
