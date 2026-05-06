#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 10000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    // No further global properties to check.
    // The problem only asks for two positive integers n and m, both in range.
    // No leading zeros or other formatting issues are possible with readInt.

    inf.readEof();
}
