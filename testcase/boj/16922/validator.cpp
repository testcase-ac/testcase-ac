#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of Roman numeral characters to use
    int N = inf.readInt(1, 20, "N");
    inf.readEoln();  // Exactly one newline after N

    // No further input
    inf.readEof();
    return 0;
}
