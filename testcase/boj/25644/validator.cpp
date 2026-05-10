#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read the N stock prices
    inf.readInts(N, 1, 1000000000, "a_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
