#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 1 <= N <= 1e6
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read the six face values A, B, C, D, E, F: each 1 <= x <= 50
    vector<int> a = inf.readInts(6, 1, 50, "face");
    inf.readEoln();

    // No other global constraints to validate.
    inf.readEof();
    return 0;
}
