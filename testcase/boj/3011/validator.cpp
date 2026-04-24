#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of sons
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Sons' names: even natural numbers < 1e9
    vector<int> P = inf.readInts(N, 1, 999999999, "P_i");
    for (int i = 0; i < N; i++) {
        ensuref(P[i] % 2 == 0,
                "P_%d = %d is not even", i+1, P[i]);
    }
    inf.readEoln();

    // Interval [A, B]
    int A = inf.readInt(1, 1000000000, "A");
    inf.readSpace();
    int B = inf.readInt(1, 1000000000, "B");
    ensuref(A < B, "A (%d) must be less than B (%d)", A, B);
    inf.readEoln();

    inf.readEof();
    return 0;
}
