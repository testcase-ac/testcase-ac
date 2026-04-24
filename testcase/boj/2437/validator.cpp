#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of weights N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read N weights, each in [1, 1e6]
    vector<int> w = inf.readInts(N, 1, 1000000, "w_i");
    inf.readEoln();

    // No extra data
    inf.readEof();

    return 0;
}
