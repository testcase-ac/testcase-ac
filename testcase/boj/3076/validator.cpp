#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C
    int R = inf.readInt(1, 10, "R");
    inf.readSpace();
    int C = inf.readInt(1, 10, "C");
    inf.readEoln();

    // Read A and B
    int A = inf.readInt(1, 10, "A");
    inf.readSpace();
    int B = inf.readInt(1, 10, "B");
    inf.readEoln();

    inf.readEof();
    return 0;
}
