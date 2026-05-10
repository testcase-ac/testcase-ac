#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the sum of scores: non-negative integer, at most 1000
    int s = inf.readInt(0, 1000, "sum");
    inf.readSpace();
    // Read the difference of scores: non-negative integer, at most 1000
    int d = inf.readInt(0, 1000, "diff");
    // End of line after the two numbers
    inf.readEoln();
    // No more data
    inf.readEof();

    return 0;
}
