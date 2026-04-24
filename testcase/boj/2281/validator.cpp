#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    // Read each name length on its own line
    for (int i = 0; i < n; i++) {
        inf.readInt(1, m, "length");
        inf.readEoln();
    }

    // No extra tokens
    inf.readEof();
    return 0;
}
