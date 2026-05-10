#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000000000, "K");
    inf.readEoln();

    // Read weights w_1 ... w_N
    vector<int> w = inf.readInts(N, 1, K, "w_i");
    inf.readEoln();

    // No further constraints implied by the problem
    inf.readEof();
    return 0;
}
