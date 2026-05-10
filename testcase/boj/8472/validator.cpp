#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 200, "n");
    inf.readSpace();
    int k = inf.readInt(1, 10, "k");
    inf.readEoln();

    ensuref(k < n, "k (%d) must be strictly less than n (%d)", k, n);

    // Read 3n temperatures
    vector<int> temps = inf.readInts(3 * n, 1, 1000000, "temperature");
    inf.readEoln();

    inf.readEof();
}
