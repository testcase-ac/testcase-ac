#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(0, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(0, 100000, "K");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
