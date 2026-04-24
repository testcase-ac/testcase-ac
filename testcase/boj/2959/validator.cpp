#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read exactly four positive integers A, B, C, D with 0 < x < 100
    int A = inf.readInt(1, 99, "A");
    inf.readSpace();
    int B = inf.readInt(1, 99, "B");
    inf.readSpace();
    int C = inf.readInt(1, 99, "C");
    inf.readSpace();
    int D = inf.readInt(1, 99, "D");
    inf.readEoln();

    // No further global constraints implied in the statement
    inf.readEof();
    return 0;
}
