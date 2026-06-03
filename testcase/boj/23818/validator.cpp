#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 100000, "m");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "k");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        int t = inf.readInt(0, 1, "t");
        inf.readSpace();
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "relation %d has equal endpoints: %d", i + 1, a);
    }

    for (int i = 0; i < k; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readEoln();

        ensuref(a != b, "query %d has equal endpoints: %d", i + 1, a);
    }

    inf.readEof();
}
