#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(0, 15 * n, "m");
    inf.readEoln();

    // Read the array a of size n
    inf.readInts(n, 1, 1000000, "a_i");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
