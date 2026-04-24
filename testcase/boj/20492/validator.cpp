#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: the prize money
    int N = inf.readInt(1000, 10000000, "N");
    // N must be a multiple of 1000
    ensuref(N % 1000 == 0, "N must be a multiple of 1000, but got %d", N);

    inf.readEoln();
    inf.readEof();
    return 0;
}
