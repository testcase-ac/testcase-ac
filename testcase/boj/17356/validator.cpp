#include "testlib.h"
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: two integers A and B on one line
    int A = inf.readInt(0, 5000, "A");
    inf.readSpace();
    int B = inf.readInt(0, 5000, "B");
    inf.readEoln();

    // No further tokens allowed
    inf.readEof();
}
