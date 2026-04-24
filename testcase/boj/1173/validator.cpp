#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the five integers: N, m, M, T, R
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int m = inf.readInt(50, 200, "m");
    inf.readSpace();
    int M = inf.readInt(m, 200, "M"); // M must be at least m
    inf.readSpace();
    int T = inf.readInt(1, 200, "T");
    inf.readSpace();
    int R = inf.readInt(1, 200, "R");
    inf.readEoln();

    // No further global constraints to check for input validity.
    inf.readEof();
    return 0;
}
