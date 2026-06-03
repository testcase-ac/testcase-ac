#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    long long hCenti = inf.readLong(1LL, 2000000000LL, "H_centi");
    inf.readSpace();
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readLong(1LL, 2000000000LL, "H");
        inf.readEoln();
    }

    inf.readEof();
}
