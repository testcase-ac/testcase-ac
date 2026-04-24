#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read three integers a, b, c each between 1 and 100 inclusive
    int a = inf.readInt(1, 100, "a");
    inf.readSpace();
    int b = inf.readInt(1, 100, "b");
    inf.readSpace();
    int c = inf.readInt(1, 100, "c");
    // End of the only line
    inf.readEoln();
    // No more content
    inf.readEof();

    return 0;
}
