#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read d and t as specified
    int d = inf.readInt(2, 50, "d");
    inf.readSpace();
    int t = inf.readInt(1, 2000000000, "t");
    // End of the single line
    inf.readEoln();
    // No more input
    inf.readEof();

    return 0;
}
