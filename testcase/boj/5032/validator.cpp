#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read e, f, c according to problem constraints:
    // e, f are non-negative integers < 1000
    // c is an integer with 1 < c < 2000, i.e., c in [2,1999]
    int e = inf.readInt(0, 999, "e");
    inf.readSpace();
    int f = inf.readInt(0, 999, "f");
    inf.readSpace();
    int c = inf.readInt(2, 1999, "c");
    inf.readEoln();

    // No additional global properties to enforce.
    // Just ensure end of file follows immediately.
    inf.readEof();
    return 0;
}
