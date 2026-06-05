#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 2000, "Q");
    inf.readSpace();
    int c = inf.readInt(1, 200000, "C");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, c, "CAP_i");
    }
    inf.readEoln();

    bool has_access = false;
    for (int i = 1; i <= q; ++i) {
        std::string op = inf.readToken("A|B|C|F", "operation");
        if (op == "A") {
            inf.readSpace();
            inf.readInt(1, n, "page");
            has_access = true;
        }
        inf.readEoln();
    }

    ensuref(has_access, "at least one access operation is required");
    inf.readEof();
}
