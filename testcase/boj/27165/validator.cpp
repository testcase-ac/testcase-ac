#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    vector<int> a = inf.readInts(n + 1, 0, 10, "a_i");
    inf.readEoln();
    ensuref(a[0] >= 1, "a_0 must be at least 1, found %d", a[0]);

    inf.readInt(1, n, "x");
    inf.readEoln();
    inf.readEof();
}
