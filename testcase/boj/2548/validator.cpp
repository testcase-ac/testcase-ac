#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of natural numbers
    int N = inf.readInt(1, 20000, "N");
    inf.readEoln();

    // Read the N natural numbers A_i
    vector<int> A = inf.readInts(N, 1, 10000, "A_i");
    inf.readEoln();

    // No more input
    inf.readEof();

    return 0;
}
