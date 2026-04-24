#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: two integers X and Y on one line
    int X = inf.readInt(1, 1000000000, "X");
    inf.readSpace();
    int Y = inf.readInt(0, X, "Y");
    inf.readEoln();
    inf.readEof();

    return 0;
}
