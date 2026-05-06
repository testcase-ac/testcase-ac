#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of values
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read N natural numbers, each between 1 and 1000 inclusive
    inf.readInts(N, 1, 1000, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
