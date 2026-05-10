#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 500000, "N");
    inf.readEoln();

    // Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 0, 1, "A_i");
    inf.readEoln();

    // Check A_1 == 0 and A_N == 0
    ensuref(A[0] == 0, "A_1 must be 0 (station 1 is always a normal station)");
    ensuref(A[N-1] == 0, "A_N must be 0 (station N is always a normal station)");

    inf.readEof();
}
