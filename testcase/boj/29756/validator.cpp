#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 10, "K");
    inf.readEoln();

    // Read scores s_i
    vector<int> s = inf.readInts(N, 1, 1000, "s_i");
    inf.readEoln();

    // Read health costs h_i
    vector<int> h = inf.readInts(N, 1, 100, "h_i");
    inf.readEoln();

    // No further input
    inf.readEof();
    return 0;
}
