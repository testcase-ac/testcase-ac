#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readSpace();
    inf.readLong(1LL, 2000000000LL, "k");
    inf.readEoln();

    long long totalRain = 0;
    for (int i = 1; i <= m; ++i) {
        int t = inf.readInt(1, n, "t_i");
        inf.readSpace();
        long long r = inf.readLong(1LL, 1000000000LL, "r_i");
        inf.readEoln();

        totalRain += r;
        ensuref(totalRain <= 2000000000LL,
                "sum of r_i exceeds 2000000000 after rain %d: %lld",
                i,
                totalRain);
    }

    inf.readEof();
}
