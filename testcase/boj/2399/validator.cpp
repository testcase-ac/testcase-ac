#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and validate its range
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    // Read the n coordinates, each between 0 and 1e9
    inf.readLongs(n, 0LL, 1000000000LL, "x");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
