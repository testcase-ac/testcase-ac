#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // This is an INPUT validator, not an output checker.
    // We only validate that the input to the problem (i.e., N) is correct.

    // Read N
    int N = inf.readInt(2, 50, "N");
    inf.readEoln();

    // No more data allowed
    inf.readEof();
}
