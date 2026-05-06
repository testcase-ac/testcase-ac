#include "testlib.h"
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer n, 1 ≤ n ≤ 5000
    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    // No further input
    inf.readEof();
}
