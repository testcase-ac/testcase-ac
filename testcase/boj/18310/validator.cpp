#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of houses
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read positions of the houses
    inf.readInts(N, 1, 100000, "x_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
