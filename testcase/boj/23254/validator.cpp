#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 200000, "M");
    inf.readEoln();

    // Read array a of size M
    vector<int> a = inf.readInts(M, 1, 100, "a_i");
    inf.readEoln();

    // Read array b of size M
    vector<int> b = inf.readInts(M, 1, 100, "b_i");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
