#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(-1000, 1000, "x");
        inf.readSpace();
        inf.readInt(-1000, 1000, "y");
        inf.readEoln();
    }

    for (int query = 1; query <= q; ++query) {
        std::string op = inf.readToken("U|Q", "op");
        inf.readSpace();

        if (op == "U") {
            inf.readInt(1, n, "i");
            inf.readSpace();
            inf.readInt(-1000, 1000, "x");
            inf.readSpace();
            inf.readInt(-1000, 1000, "y");
            inf.readEoln();
        } else {
            int i = inf.readInt(1, n, "i");
            inf.readSpace();
            // CHECK: The input section states I <= J; it does not require
            // an internal checkpoint even though the story discusses skipping.
            inf.readInt(i, n, "j");
            inf.readEoln();
        }
    }

    inf.readEof();
}
