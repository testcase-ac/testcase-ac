#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        std::string type = inf.readToken("S|D", "type");
        inf.readSpace();
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        // CHECK: The statement does not explicitly ban self-pairs or duplicate constraints.
        (void)type;
        (void)a;
        (void)b;
    }

    inf.readEof();
}
