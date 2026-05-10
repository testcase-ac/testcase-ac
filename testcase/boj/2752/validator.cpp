#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read exactly three integers in one line, each in [1, 1e6], all distinct.
    int a = inf.readInt(1, 1000000, "a");
    inf.readSpace();
    int b = inf.readInt(1, 1000000, "b");
    inf.readSpace();
    int c = inf.readInt(1, 1000000, "c");
    inf.readEoln();

    // Check distinctness
    ensuref(a != b, "Numbers a and b must be distinct, but both are %d", a);
    ensuref(a != c, "Numbers a and c must be distinct, but both are %d", a);
    ensuref(b != c, "Numbers b and c must be distinct, but both are %d", b);

    inf.readEof();
    return 0;
}
