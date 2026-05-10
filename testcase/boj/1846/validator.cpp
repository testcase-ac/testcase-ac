#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: size of the board, number of rooks to place
    int N = inf.readInt(3, 100000, "N");
    inf.readEoln();

    // No further input; ensure end of file
    inf.readEof();
    return 0;
}
