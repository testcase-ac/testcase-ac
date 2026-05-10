#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: A, B, C
    int A = inf.readInt(0, 5000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 60, "B");
    inf.readSpace();
    int C = inf.readInt(1, 2000, "C");
    inf.readEoln();

    // Second line: T
    int T = inf.readInt(1, 2000, "T");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
