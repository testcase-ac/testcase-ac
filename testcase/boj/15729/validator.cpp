#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the N bits, each must be 0 or 1
    inf.readInts(N, 0, 1, "a_i");
    inf.readEoln();

    // No extra data
    inf.readEof();

    return 0;
}
