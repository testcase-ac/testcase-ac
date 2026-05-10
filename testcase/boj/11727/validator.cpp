#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: 1 ≤ n ≤ 1000
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
