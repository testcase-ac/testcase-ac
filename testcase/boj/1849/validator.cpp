#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read A[1] through A[N]
    for (int i = 1; i <= N; i++) {
        // A[i] = number of larger elements before i in the permutation
        // so 0 <= A[i] <= N - i
        int maxAi = N - i;
        inf.readInt(0, maxAi, "A_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
