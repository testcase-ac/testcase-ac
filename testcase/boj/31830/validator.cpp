#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200000, "N");
    inf.readSpace();
    int q = inf.readInt(3, 200000, "Q");
    inf.readEoln();

    string s = inf.readToken("[A-Z]+", "S");
    ensuref((int)s.size() == n, "S length must be N: expected %d, found %d", n, (int)s.size());
    inf.readEoln();

    bool hasTypeOne = false;
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(1, n, "r");
        ensuref(l <= r, "query %d has l > r: %d > %d", i, l, r);
        inf.readEoln();

        if (type == 1) {
            hasTypeOne = true;
        }
    }

    ensuref(hasTypeOne, "at least one type-1 query is required");
    inf.readEof();
}
