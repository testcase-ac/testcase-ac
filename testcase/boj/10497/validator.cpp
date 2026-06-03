#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 30, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        string kind = inf.readToken("rectangle|circle", "target_type");
        inf.readSpace();

        if (kind == "rectangle") {
            int x1 = inf.readInt(-1000, 1000, "x1");
            inf.readSpace();
            int y1 = inf.readInt(-1000, 1000, "y1");
            inf.readSpace();
            int x2 = inf.readInt(-1000, 1000, "x2");
            inf.readSpace();
            int y2 = inf.readInt(-1000, 1000, "y2");
            inf.readEoln();

            ensuref(x1 < x2,
                    "rectangle %d must satisfy x1 < x2: %d >= %d",
                    i,
                    x1,
                    x2);
            ensuref(y1 < y2,
                    "rectangle %d must satisfy y1 < y2: %d >= %d",
                    i,
                    y1,
                    y2);
        } else {
            inf.readInt(-1000, 1000, "x");
            inf.readSpace();
            inf.readInt(-1000, 1000, "y");
            inf.readSpace();
            inf.readInt(1, 1000, "r");
            inf.readEoln();
        }
    }

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(-1000, 1000, "x");
        inf.readSpace();
        inf.readInt(-1000, 1000, "y");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
