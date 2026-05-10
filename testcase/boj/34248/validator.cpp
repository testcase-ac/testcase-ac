#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 1, 2, "A_i");
    inf.readEoln();

    // No extra global properties are guaranteed in the statement except ranges,
    // so no need to simulate the game here from validator's perspective.

    inf.readEof();
}
