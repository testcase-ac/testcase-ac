#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    // CHECK: The statement describes K as a count of breed IDs but omits
    // numeric bounds; cap it to the number of cows, the maximum useful count.
    int k = inf.readInt(0, n, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(0LL, 1000000000LL, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
