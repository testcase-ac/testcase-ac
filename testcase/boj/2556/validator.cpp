#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of lines to print stars
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
