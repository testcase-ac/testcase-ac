#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "x");
        inf.readSpace();
        int y = inf.readInt(1, n, "y");
        inf.readSpace();
        string kind = inf.readToken("L|T", "kind");
        inf.readEoln();

        ensuref(x != y, "statement %d uses the same cow twice: %d", i, x);
        (void)kind;
    }

    inf.readEof();
}
