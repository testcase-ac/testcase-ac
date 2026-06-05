#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 200, "n");
    inf.readSpace();
    int q = inf.readInt(3, 200, "q");
    inf.readEoln();

    string s = inf.readToken("[A-Z]{3,200}", "s");
    ensuref((int)s.size() == n, "s length must be n: got %d, expected %d", (int)s.size(), n);
    inf.readEoln();

    bool hasTypeOne = false;
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(l, n, "r");
        inf.readEoln();

        if (type == 1) {
            hasTypeOne = true;
        }
    }

    ensuref(hasTypeOne, "at least one type 1 query is required");
    inf.readEof();
}
