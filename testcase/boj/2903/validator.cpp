#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of iterations, must be between 1 and 15 inclusive.
    int N = inf.readInt(1, 15, "N");
    inf.readEoln();

    // No extra input allowed.
    inf.readEof();
    return 0;
}
