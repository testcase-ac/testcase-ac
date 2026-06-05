#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound the number of test cases; cap it to
    // keep validation below the local practical scalar-token limit.
    int n = inf.readInt(1, 5000, "N");
    inf.readEoln();

    for (int tc = 1; tc <= n; ++tc) {
        setTestCase(tc);

        int s = inf.readInt(1, 100, "S");
        inf.readSpace();
        int p = inf.readInt(s + 1, 500, "P");
        inf.readEoln();

        for (int i = 1; i <= p; ++i) {
            inf.readInt(0, 10000, "x");
            inf.readSpace();
            inf.readInt(0, 10000, "y");
            inf.readEoln();
        }
    }

    inf.readEof();
}
