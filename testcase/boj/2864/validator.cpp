#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and B on the same line
    int A = inf.readInt(1, 1000000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 1000000, "B");
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
