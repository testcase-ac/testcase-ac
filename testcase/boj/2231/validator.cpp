#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single input N: 1 ≤ N ≤ 1,000,000
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();  // End of line after N

    // No further input
    inf.readEof();
    return 0;
}
