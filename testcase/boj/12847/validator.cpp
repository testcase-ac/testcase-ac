#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(0, n, "m");
    inf.readEoln();

    // Read daily wages T_i
    inf.readInts(n, 1, 1000000, "T_i");
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
