#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: n
    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    // Second line: a, b, c
    int a = inf.readInt(-5, -1, "a");
    inf.readSpace();
    int b = inf.readInt(-10000000, 10000000, "b");
    inf.readSpace();
    int c = inf.readInt(-30000000, 30000000, "c");
    inf.readEoln();

    // Third line: x_1 ... x_n
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 100, "x_i");
    }
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
