#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAXN = 200000;
    const int MAXM = 200000;
    const int LIM = (1 << 20) - 1;

    int n = inf.readInt(1, MAXN, "n");
    inf.readEoln();

    // Read array A_1..A_n
    {
        vector<int> a = inf.readInts(n, 0, LIM, "a_i");
        inf.readEoln();
    }

    int m = inf.readInt(1, MAXM, "m");
    inf.readEoln();

    bool hasType3 = false;

    for (int i = 0; i < m; ++i) {
        int t = inf.readInt(1, 3, "t");
        if (t == 1 || t == 2) {
            inf.readSpace();
            int L = inf.readInt(1, n, "L");
            inf.readSpace();
            int R = inf.readInt(1, n, "R");
            inf.readSpace();
            int X = inf.readInt(0, LIM, "X");
            inf.readEoln();

            ensuref(L <= R, "Query %d: L (%d) must be <= R (%d)", i + 1, L, R);
        } else { // t == 3
            hasType3 = true;
            inf.readSpace();
            int L = inf.readInt(1, n, "L");
            inf.readSpace();
            int R = inf.readInt(1, n, "R");
            inf.readEoln();

            ensuref(L <= R, "Query %d: L (%d) must be <= R (%d)", i + 1, L, R);
        }
    }

    ensuref(hasType3, "There must be at least one type-3 query");

    inf.readEof();
}
