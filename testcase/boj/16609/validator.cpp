#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of balloons/canisters
    int n = inf.readInt(1, 200000, "n");
    inf.readEoln();

    // Read amounts of helium in the canisters
    vector<int> c = inf.readInts(n, 0, n, "c_i");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
