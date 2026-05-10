#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int N_MAX = 500000;
    const int M_MAX = 200000;
    const int MAX_A = (1 << 30) - 1;

    int n = inf.readInt(1, N_MAX, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n, 0, MAX_A, "a_i");
    inf.readEoln();

    int m = inf.readInt(1, M_MAX, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        char type = (char)inf.readChar();
        ensuref(type == '&' || type == '|' || type == '?',
                "Query %d: invalid type '%c', expected '&', '|' or '?'",
                i + 1, type);

        inf.readSpace();
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(1, n, "r");
        ensuref(l <= r, "Query %d: l (%d) must be <= r (%d)", i + 1, l, r);

        if (type == '&' || type == '|') {
            inf.readSpace();
            int x = inf.readInt(0, MAX_A, "x");
        }
        inf.readEoln();
    }

    inf.readEof();
}
