#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{2,50}", "S");
    ensuref((int)s.size() == n, "S length must be N: expected %d, found %d", n, (int)s.size());
    inf.readEoln();

    int q = inf.readInt(1, 100, "Q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        int l = inf.readInt(1, n - 1, "l");
        inf.readSpace();
        int r = inf.readInt(l + 1, n, "r");
        inf.readEoln();
    }

    inf.readEof();
}
