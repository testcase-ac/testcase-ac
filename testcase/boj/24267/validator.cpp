#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: the size of the input, must be between 1 and 500000 inclusive.
    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    // No more input tokens allowed.
    inf.readEof();
    return 0;
}
