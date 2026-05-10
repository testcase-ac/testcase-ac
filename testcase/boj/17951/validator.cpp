#include "testlib.h"
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, K
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // Second line: N integers x_i
    vector<int> x = inf.readInts(N, 0, 20, "x_i");
    inf.readEoln();

    // No further lines allowed
    inf.readEof();
}
