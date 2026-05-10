#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: n, a, b
    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int a = inf.readInt(1, 10, "a");
    inf.readSpace();
    int b = inf.readInt(1, 10, "b");
    inf.readEoln();

    // Second line: first row of grid
    vector<int> row1 = inf.readInts(n, 1, 100000, "row1_i");
    inf.readEoln();

    // Third line: second row of grid
    vector<int> row2 = inf.readInts(n, 1, 100000, "row2_i");
    inf.readEoln();

    inf.readEof();
}
