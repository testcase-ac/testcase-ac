#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A: integer on the first line, 1 <= A <= 100
    int A = inf.readInt(1, 100, "A");
    inf.readEoln();

    // Read B: integer on the second line, 1 <= B <= 100
    int B = inf.readInt(1, 100, "B");
    inf.readEoln();

    // No extra characters after the second line
    inf.readEof();
    return 0;
}
