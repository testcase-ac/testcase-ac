#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N: length of the sequence
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read N integers a_i with |a_i| <= 2,000,000
    // Use int range [-2000000, 2000000]
    vector<int> a = inf.readInts(N, -2000000, 2000000, "a_i");
    inf.readEoln();

    // No further global properties implied by the problem.
    // (Sorting behavior is for the solution, not for the validator.)

    inf.readEof();
}
