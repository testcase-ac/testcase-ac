#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "n");
    ensuref(n % 2 == 0, "n must be even, got %d", n);
    inf.readEoln();

    string s = inf.readToken("[()]{2,300000}", "S");
    ensuref((int)s.size() == n, "S length must be n: length=%d n=%d", (int)s.size(), n);
    inf.readEoln();

    int q = inf.readInt(1, 300000, "q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();

        if (type == 1) {
            inf.readInt(1, n, "k");
        } else {
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            int r = inf.readInt(1, n, "r");
            ensuref(l <= r, "query %d has l > r: l=%d r=%d", i, l, r);
        }
        inf.readEoln();
    }

    inf.readEof();
}
