#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and L
    long long N = inf.readLong(1LL, 1000000000LL, "N");
    inf.readSpace();
    int L = inf.readInt(2, 100, "L");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
