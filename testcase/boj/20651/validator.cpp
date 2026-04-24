#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of flowers
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Read petal counts p_1 ... p_N
    inf.readInts(N, 1, 1000, "p_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
