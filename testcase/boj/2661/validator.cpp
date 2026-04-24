#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of digits in the sequence
    int N = inf.readInt(1, 80, "N");

    // After N, there must be exactly one end-of-line
    inf.readEoln();

    // No extra characters after the single test case
    inf.readEof();

    return 0;
}
