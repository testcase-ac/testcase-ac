#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    // CHECK: The statement gives independent bounds for n and m and does not
    // require m <= n; in that case there are simply no length-m windows.
    int m = inf.readInt(1, 10000, "m");
    inf.readSpace();
    int c = inf.readInt(0, 10000, "c");
    inf.readEoln();

    inf.readInts(n, 0, 1000000, "a_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
