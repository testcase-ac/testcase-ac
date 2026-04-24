#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read capacities A, B, C: each between 1 and 200 inclusive
    int A = inf.readInt(1, 200, "A");
    inf.readSpace();
    int B = inf.readInt(1, 200, "B");
    inf.readSpace();
    int C = inf.readInt(1, 200, "C");
    inf.readEoln();

    // No other constraints or global properties to check
    inf.readEof();
    return 0;
}
