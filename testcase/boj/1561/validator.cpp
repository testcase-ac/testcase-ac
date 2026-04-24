#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    long long N = inf.readLong(1LL, 2000000000LL, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Read M ride times
    inf.readInts(M, 1, 30, "t_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
