#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first line: A B
    int A = inf.readInt(1, 100, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100, "B");
    inf.readEoln();

    // Read second line: C D
    int C = inf.readInt(1, 100, "C");
    inf.readSpace();
    int D = inf.readInt(1, 100, "D");
    inf.readEoln();

    // End of file
    inf.readEof();
    return 0;
}
