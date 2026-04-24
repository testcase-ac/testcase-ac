#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int t = inf.readInt(1, 500, "t");
    inf.readEoln();

    // Sum of n over all test cases must not exceed 1e5
    long long total_n = 0;
    for (int tc = 0; tc < t; tc++) {
        int n = inf.readInt(1, 100000, "n");
        total_n += n;
        inf.readEoln();
    }
    ensuref(total_n <= 100000LL,
            "Sum of n over all test cases must be at most 100000, but got %lld",
            total_n);

    inf.readEof();
    return 0;
}
