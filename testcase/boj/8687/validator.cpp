#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "m");
    inf.readEoln();

    // Read the grid: n rows, each with m entries of 0 or 1
    for (int i = 0; i < n; i++) {
        vector<int> row = inf.readInts(m, 0, 1, "cell");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
