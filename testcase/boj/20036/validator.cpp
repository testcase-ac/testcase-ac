#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n: number of balls
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read the n ball values, one per line
    for (int i = 0; i < n; i++) {
        long long v = inf.readLong(1LL, 1000000000LL, "v_i");
        inf.readEoln();
    }

    // No extra content
    inf.readEof();
    return 0;
}
