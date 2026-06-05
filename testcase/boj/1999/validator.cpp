#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 250, "N");
    inf.readSpace();
    int b = inf.readInt(1, n, "B");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int row = 1; row <= n; ++row) {
        for (int col = 1; col <= n; ++col) {
            if (col > 1) {
                inf.readSpace();
            }
            inf.readInt(0, 250, "elevation");
        }
        inf.readEoln();
    }

    int query_limit = n - b + 1;
    for (int query = 1; query <= k; ++query) {
        inf.readInt(1, query_limit, "i");
        inf.readSpace();
        inf.readInt(1, query_limit, "j");
        inf.readEoln();
    }

    inf.readEof();
}
