#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the size of the triangle
    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    // Read each row of the triangle
    for (int i = 1; i <= n; i++) {
        // Each row i has exactly i integers in [0, 9999]
        inf.readInts(i, 0, 9999, "a");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
