#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // To check for duplicate n values (not required by statement, but can be useful)
    // set<long long> seen_n;

    for (int tc = 0; tc < T; ++tc) {
        // Read n
        long long n = inf.readLong(2LL, 1000000000000000LL, "n");
        inf.readEoln();

        // No further constraints to check per test case
        // (No duplicate n restriction, no further global properties)
    }

    inf.readEof();
}
