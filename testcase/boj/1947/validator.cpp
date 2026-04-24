#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of participants, must be between 1 and 1,000,000.
    int N = inf.readInt(1, 1000000, "N");
    // After N, there must be exactly one newline.
    inf.readEoln();
    // No extra characters after the single test case.
    inf.readEof();

    return 0;
}
