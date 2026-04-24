#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of terms, must be between 0 and 35 inclusive
    int n = inf.readInt(0, 35, "n");
    inf.readEoln();

    // No further input
    inf.readEof();
}
