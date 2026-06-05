#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "N");
    inf.readEoln();

    inf.readLong(-2147483648LL, 2147483647LL, "A_1");
    for (int i = 2; i <= n; ++i) {
        inf.readSpace();
        inf.readLong(-2147483648LL, 2147483647LL, "A_i");
    }
    inf.readEoln();
    inf.readEof();
}
