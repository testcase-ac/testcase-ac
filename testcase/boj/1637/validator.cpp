#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of descriptions
    int N = inf.readInt(1, 20000, "N");
    inf.readEoln();

    // Each of the next N lines has three integers: A, C, B
    for (int i = 0; i < N; i++) {
        long long A = inf.readLong(1LL, 2147483647LL, "A_i");
        inf.readSpace();
        long long C = inf.readLong(1LL, 2147483647LL, "C_i");
        inf.readSpace();
        long long B = inf.readLong(1LL, 2147483647LL, "B_i");
        inf.readEoln();
        // Sequences with A > C are allowed (they contribute no elements).
    }

    inf.readEof();
    return 0;
}
