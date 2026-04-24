#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n
    int n = inf.readInt(2, 100, "n");
    inf.readEoln();

    // Read the n x n grid
    for (int i = 0; i < n; i++) {
        // Read one row of n integers, each between 0 and 200
        vector<int> row = inf.readInts(n, 0, 200, "a_i");
        inf.readEoln();
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
