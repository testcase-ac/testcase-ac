#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // n: number of boxes
    int n = inf.readInt(1, 5000, "n");
    inf.readEoln();

    // Read sizes A_i
    vector<int> a = inf.readInts(n, 1, 100000, "A_i");
    inf.readEoln();

    // No extra global constraints in statement (no guarantees about answer range
    // beyond what naturally follows from n), so no additional checks needed.

    inf.readEof();
}
