#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000000, "N");
    inf.readEoln();

    // Read sequence A of size N
    vector<int> A = inf.readInts(N, 1, 1000000, "A_i");
    inf.readEoln();

    // No additional global properties to check for this problem.

    inf.readEof();
    return 0;
}
