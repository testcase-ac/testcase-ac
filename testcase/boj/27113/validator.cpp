#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "N");
    inf.readSpace();
    long long m = inf.readLong(2LL, 1000000000LL, "M");
    inf.readEoln();

    for (int i = 1; i <= n - 1; ++i) {
        int x = inf.readInt(0, 2, "x_i");
        long long previous_column = 0;

        for (int j = 1; j <= x; ++j) {
            inf.readSpace();
            long long c = inf.readLong(1LL, m, "c_ij");
            ensuref(previous_column < c,
                    "sensor columns must increase on boundary %d: previous=%lld current=%lld",
                    i, previous_column, c);
            previous_column = c;

            inf.readSpace();
            inf.readToken("L|R", "d_ij");
        }

        inf.readEoln();
    }

    inf.readEof();
}
