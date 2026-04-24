#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read two integers A and B with 0 < A, B < 10
    int A = inf.readInt(1, 9, "A");
    inf.readSpace();
    int B = inf.readInt(1, 9, "B");
    inf.readEoln();

    inf.readEof();
    return 0;
}
