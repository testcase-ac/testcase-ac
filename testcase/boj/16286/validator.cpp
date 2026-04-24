#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read W and n
    long long W = inf.readLong(1LL, 1000000000LL, "W");
    inf.readSpace();
    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    // Read the weights array
    vector<long long> w = inf.readLongs(n, 1LL, W, "w_i");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
