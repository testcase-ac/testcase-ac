#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases, allow from 0 up to 100000
    int t = inf.readInt(0, 100000, "t");
    inf.readEoln();

    for (int tc = 0; tc < t; ++tc) {
        // n in [0, 4e9]
        long long n = inf.readLong(0LL, 4000000000LL, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
