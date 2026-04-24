#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer n with constraints 1 <= n <= 116
    inf.readInt(1, 116, "n");
    // After reading n, there must be exactly one newline
    inf.readEoln();
    // No extra data after the single test case
    inf.readEof();
    return 0;
}
