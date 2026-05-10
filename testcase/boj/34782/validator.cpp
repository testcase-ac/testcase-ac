#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n, d, m
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int d = inf.readInt(1, 100000, "d");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    // Read s_1 .. s_n
    vector<int> s = inf.readInts(n, 1, 100000, "s_i");
    inf.readEoln();

    inf.readEof();
}
