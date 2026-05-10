#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    // No further input
    inf.readEof();
}
