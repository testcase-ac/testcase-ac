#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readSpace();
    int m = inf.readInt(1, 500, "M");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readLong(1LL, 1000000000LL, "height");
        }
        inf.readEoln();
    }

    inf.readEof();
}
