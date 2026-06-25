#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 50, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readSpace();
    inf.readInt(1, 1000000, "T");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        ensuref(a != b, "road %d connects duplicate building %d", i, a);

        if (type == 1) {
            inf.readEoln();
        } else {
            inf.readSpace();
            int c = inf.readInt(1, n, "c");
            ensuref(a != c && b != c,
                    "road %d connects duplicate building among %d %d %d",
                    i, a, b, c);
            inf.readEoln();
        }
    }

    inf.readEof();
}
