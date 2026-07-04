#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int r = inf.readInt(1, 1000000, "R");
        inf.readSpace();
        int k = inf.readInt(1, 10000, "K");
        inf.readEoln();

        long long rr = 1LL * r * r;
        for (int i = 1; i <= k; ++i) {
            int x = inf.readInt(-1000000, 1000000, "X");
            inf.readSpace();
            int y = inf.readInt(-1000000, 1000000, "Y");
            inf.readSpace();
            int rocketSpeed = inf.readInt(1, 1000000, "rocket_speed");
            inf.readSpace();
            int virusSpeed = inf.readInt(1, 1000000, "virus_speed");
            inf.readEoln();

            long long dist2 = 1LL * x * x + 1LL * y * y;
            ensuref(dist2 >= rr,
                    "case %d ship %d is inside the planet: (%d, %d), R=%d",
                    tc,
                    i,
                    x,
                    y,
                    r);
        }
    }

    inf.readEof();
}
