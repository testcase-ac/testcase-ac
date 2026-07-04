#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 20, "N");
    inf.readSpace();
    int k = inf.readInt(1, 30, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        int a = inf.readInt(1, n, "a");
        inf.readSpace();
        int b = inf.readInt(1, n, "b");
        inf.readSpace();
        int sa = inf.readInt(0, 9, "sa");
        inf.readSpace();
        int sb = inf.readInt(0, 9, "sb");
        inf.readEoln();

        ensuref(a != b, "game %d uses the same player twice: %d", i, a);
        ensuref(sa != sb, "game %d is a draw: %d %d", i, sa, sb);
        // CHECK: the statement forbids playing oneself, but does not forbid
        // repeated games between the same two players.
    }

    inf.readEof();
}
