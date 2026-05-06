#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read three lines, each an integer in [100, 999]
    int A = inf.readInt(100, 999, "A");
    inf.readEoln();
    int B = inf.readInt(100, 999, "B");
    inf.readEoln();
    int C = inf.readInt(100, 999, "C");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
