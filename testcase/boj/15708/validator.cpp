#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "T");
    inf.readSpace();
    inf.readInt(1, 100000, "P");
    inf.readEoln();

    inf.readInts(n, 1, 100000, "K_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
