#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read R and C with their constraints
    int R = inf.readInt(1, 12117, "R");
    inf.readSpace();
    int C = inf.readInt(1, 12117, "C");
    inf.readEoln();

    // No further global constraints to check
    inf.readEof();
    return 0;
}
