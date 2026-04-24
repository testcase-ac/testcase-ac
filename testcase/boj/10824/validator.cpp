#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read four natural numbers A, B, C, D in [1, 1e6]
    int A = inf.readInt(1, 1000000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 1000000, "B");
    inf.readSpace();
    int C = inf.readInt(1, 1000000, "C");
    inf.readSpace();
    int D = inf.readInt(1, 1000000, "D");
    inf.readEoln();

    inf.readEof();
    return 0;
}
