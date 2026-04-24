#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the three positive integers w, h, L with given constraints.
    int w = inf.readInt(1, 100000, "w");
    inf.readSpace();
    int h = inf.readInt(1, 100000, "h");
    inf.readSpace();
    int L = inf.readInt(1, 100000, "L");
    inf.readEoln();

    // No further global conditions to check.
    inf.readEof();
    return 0;
}
