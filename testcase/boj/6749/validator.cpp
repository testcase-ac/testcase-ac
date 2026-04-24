#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read age of youngest child Y: 0 ≤ Y ≤ 50
    int Y = inf.readInt(0, 50, "Y");
    inf.readEoln();

    // Read age of middle child M: Y ≤ M ≤ 50
    int M = inf.readInt(Y, 50, "M");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
