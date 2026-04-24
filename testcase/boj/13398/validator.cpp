#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of elements
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read the sequence of n integers, each between -1000 and 1000
    vector<int> a = inf.readInts(n, -1000, 1000, "a");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
