#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read sequence A
    vector<int> A = inf.readInts(N, 1, 1000000, "A_i");
    inf.readEoln();

    // No additional global constraints implied by the problem
    // (operations are just described, no guarantee like "answer <= X"
    // or structure constraints that need simulation).

    inf.readEof();
}
