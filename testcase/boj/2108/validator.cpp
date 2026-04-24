#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of values, must be odd, 1 ≤ N ≤ 500,000
    int N = inf.readInt(1, 500000, "N");
    ensuref(N % 2 == 1, "N must be odd, but got %d", N);
    inf.readEoln();

    // Read the N integers, one per line, each in range [-4000, 4000]
    for (int i = 0; i < N; i++) {
        inf.readInt(-4000, 4000, "a_i");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
