#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of menu items
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    // Read the Scoville indices
    // Each must be in [0, 2^31-1]
    inf.readLongs(N, 0LL, 2147483647LL, "S_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
