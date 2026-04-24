#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    // Read the array of n natural numbers (1 to 1e6)
    inf.readInts(n, 1, 1000000, "a_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
