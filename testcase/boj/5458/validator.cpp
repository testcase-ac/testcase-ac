#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for the number of test cases.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int s1 = inf.readInt(0, 20, "s1");
        inf.readSpace();
        int s2 = inf.readInt(0, 20, "s2");
        inf.readSpace();
        int s3 = inf.readInt(0, 20, "s3");
        inf.readSpace();
        int f1 = inf.readInt(1, 3, "f1");
        inf.readSpace();
        int f2 = inf.readInt(1, 3, "f2");
        inf.readSpace();
        int f3 = inf.readInt(1, 3, "f3");
        inf.readEoln();

        ensuref(s1 + s2 + s3 >= 1,
                "at least one stack must be non-empty, got %d %d %d",
                s1, s2, s3);
        ensuref(f1 != 1, "player 1 cannot choose himself as favorite");
        ensuref(f2 != 2, "player 2 cannot choose himself as favorite");
        ensuref(f3 != 3, "player 3 cannot choose himself as favorite");
    }

    inf.readEof();
}
