#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int c = inf.readInt(1, 100, "c");
    inf.readEoln();

    for (int tc = 1; tc <= c; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(2, 100000, "n");
        inf.readSpace();
        // CHECK: the Korean primary statement says difficulties are <= 1000,
        // while the English variant says less than 1000. Follow the primary.
        int l1 = inf.readInt(0, 1000, "l1");
        inf.readSpace();
        int l2 = inf.readInt(0, 1000, "l2");
        inf.readSpace();
        int s1 = inf.readInt(0, 1000, "s1");
        inf.readSpace();
        int s2 = inf.readInt(0, 1000, "s2");
        inf.readEoln();

        inf.readInts(n - 1, 0, 1000, "pass_1_to_2");
        inf.readEoln();
        inf.readInts(n - 1, 0, 1000, "dribble_1");
        inf.readEoln();
        inf.readInts(n - 1, 0, 1000, "pass_2_to_1");
        inf.readEoln();
        inf.readInts(n - 1, 0, 1000, "dribble_2");
        inf.readEoln();

        (void)l1;
        (void)l2;
        (void)s1;
        (void)s2;
    }

    inf.readEof();
}
