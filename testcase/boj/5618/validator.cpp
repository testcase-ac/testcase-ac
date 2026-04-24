#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: must be 2 or 3
    int n = inf.readInt(2, 3, "n");
    inf.readEoln();

    // Read exactly n natural numbers in [1, 1e8]
    vector<int> a = inf.readInts(n, 1, 100000000, "a");
    inf.readEoln();

    inf.readEof();
    return 0;
}
