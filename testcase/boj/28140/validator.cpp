#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 1000000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 1000000, "Q");
    inf.readEoln();

    string s = inf.readToken("[A-Z]+", "S");
    ensuref((int)s.size() == n, "S length must equal N: length=%d N=%d", (int)s.size(), n);
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        int l = inf.readInt(0, n - 1, "l");
        inf.readSpace();
        int r = inf.readInt(0, n - 1, "r");
        ensuref(l <= r, "query %d must satisfy l <= r: l=%d r=%d", i + 1, l, r);
        inf.readEoln();
    }

    inf.readEof();
}
