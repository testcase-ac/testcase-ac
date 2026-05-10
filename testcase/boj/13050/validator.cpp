#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    // Read array a
    vector<int> a = inf.readInts(n, -1000000000, 1000000000, "a_i");
    inf.readEoln();

    // Read array b
    vector<int> b = inf.readInts(m, -1000000000, 1000000000, "b_j");
    inf.readEoln();

    inf.readEof();
}
