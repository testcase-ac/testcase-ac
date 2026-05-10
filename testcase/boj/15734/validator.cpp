#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L, R, A
    int L = inf.readInt(0, 100, "L");
    inf.readSpace();
    int R = inf.readInt(0, 100, "R");
    inf.readSpace();
    int A = inf.readInt(0, 100, "A");
    inf.readEoln();

    inf.readEof();
}
