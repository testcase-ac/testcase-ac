#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 5000, "N");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{2,5000}", "S");
    inf.readEoln();
    ensuref((int)s.size() == n, "S length is %d, expected %d", (int)s.size(), n);

    int q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int l = inf.readInt(1, n - 1, "l");
        inf.readSpace();
        int r = inf.readInt(l + 1, n, "r");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
